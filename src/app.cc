#include <sstream>
#include <iomanip>

#include "app.h"
#include "strutils.h"

#define __DEFAULT_HELP_ARGC 2

static int checkArguments(int i, int argc, char* cmdName) {
    if (i+1 <= argc-1) {
        return 0;
    }
    std::cout << "Invalid number of arguments for supplied for the command '" << cmdName << "'," << std::endl;
    std::cout << "Expected " << i << " arguments, but found " << argc-2 << "." << std::endl;
    return 1;
}

static int parseCmdFlags(int argc, char *argv[], std::unordered_map<std::string, BaseFlag*> flags) {
    // start from 2th index for flags
    for (int i = 2; i < argc; i++) {
        std::string flagName = argv[i];

        if (!strings::hasPrefix(flagName, "--")) {
            continue;
        }

        strings::trimPrefix(&flagName, "--");

        if (flags.find(flagName) == flags.end()) {
            // unexpected flag
            std::cout << "Found unexpected flag: --" << flagName << std::endl; 
            return 1;
        }

        BaseFlag* flag = flags[flagName];

        FlagType ftype = flag->type();
        switch (ftype) {
            case FlagBool:
            {
                BoolFlag* _flag = static_cast<BoolFlag*>(flag);
                _flag->value = true;
                break;
            }
            case FlagString:
            {
                StringFlag* _flag = static_cast<StringFlag*>(flag);

                if (int errCode = checkArguments(i, argc, argv[1]); errCode != 0) {
                    return errCode;
                };

                _flag->value = argv[i + 1];
                break;
            }
            case FlagInt:
            {
                IntFlag* _flag = static_cast<IntFlag*>(flag);
               
                if (int errCode = checkArguments(i, argc, argv[1]); errCode != 0) {
                    return errCode;
                };

                _flag->value = std::atoi(argv[i + 1]);
                break;
            }
            case FlagSizeT:
            {
                SizeTFlag* _flag = static_cast<SizeTFlag*>(flag);
                
                if (int errCode = checkArguments(i, argc, argv[1]); errCode != 0) {
                    return errCode;
                };

                _flag->value = std::atol(argv[i + 1]);
                break;
            }
            default:
            // unknown flag type
            std::cout << "Found unknown flag type: " << flag->type() << std::endl; 
            return 1;
        };
        // remove flag from map
        flags.erase(flagName);
    }

    for (const auto &pair : flags) {
        std::string flagName = pair.first;
        BaseFlag* flag = pair.second;
        if (flag == NULL || !flag->isRequired()) {
            continue;
        }
        std::cout << "Missing required flag '--" << flagName << "' for the command '"  << argv[1] << "'." << std::endl;
        return 1;
    }
    return 0;
}

Context CliApp::newContext() {
    Context ctx;
    ctx.appName = name;
    ctx.appShortDescription = shortDescription;
    ctx.appDescription = description;
    ctx.appVersion = version;
    return ctx;
}

bool CliApp::addCommand(Command* command) {
    if (command == NULL) {
        return false;
    }
    
    std::string cmdName = command->name;

    if (cmdName.length() > maxField) {
        maxField = cmdName.length();
    }

    commands[cmdName] = command;
    shorters[command->shorter] = cmdName;
    return true;
}

bool CliApp::exists(std::string cmdName) {
    return (commands.find(cmdName) != commands.end());
}

void CliApp::helpCallback(int argc, std::string cmdName, bool general) {
    // $bin help
    if (argc <= 2) {
        if (general) {
            if (shortDescription != "") {
                std::cout << shortDescription;
            } else {
                std::cout << name;
            }
            if (description != "") {
                std::cout << "\n\n" << description;
            }
            std::cout << "\n";
        }
        std::cout << commandsHelp << std::endl;
        std::cout << "\nUse \"" << execName << " help <command>\" for more information about a command.\n\n";
        if (general && footer != "") {
            std::cout << "\n" << footer << std::endl;
        }
        return;
    }
    // $bin help $cmdName
    if (!exists(cmdName)) {
        helpFallback(cmdName);
        return;
    }
    Command *cmd = commands[cmdName];
    if (general) {
        std::cout << "Command: " << cmd->name;
    }
    std::cout << "\nUsage: " << execName << " " << cmd->name << " options...\n";

    if (cmd->shortDescription != "") {
        std::cout << "\n" << cmd->shortDescription;
    }
    if (cmd->shortDescription != "" && cmd->description != "") {
        std::cout << "\n";
    }
    if (cmd->description != "") {
        std::cout << "\n" << cmd->description;
    }
    if (cmd->flags.empty()) {
        std::cout << std::endl;
        return;
    }
    int n = 0;
    std::cout << "\n\n" << "Supported flags:";
    for (const auto &pair: cmd->flags) {
        n++;
        std::cout << "\n " << n << ".) --" << std::left << std::setw(cmd->maxField) << pair.first << " : " << pair.second->description;
        if (!pair.second->isRequired()) {
            continue;
        }
        std::cout << " (Required)";
    }
    std::cout << std::endl;
}

void CliApp::helpFallback(std::string cmdName) {
    std::cout << name << ": " << "'" << cmdName << "'" << " is an invalid command.\n";
    std::cout << "Run '" << execName << " help' for usage.\n";
    // helpCallback(__DEFAULT_HELP_ARGC, cmdName, false);
}

void CliApp::buildHelp() {
    std::stringstream s;
    s << "\nCommands:";
    for (const auto& cmd : commands) {
        s << "\n " << std::left << std::setw(maxField) << cmd.first << " : " << cmd.second->shortDescription;
    }
    commandsHelp = s.str();
}

int CliApp::run(int argc, char *argv[]) {
    if (execName == "") {
        execName = argv[0];
    }
    // build help description
    buildHelp();

    if (argc == 1) {
        helpCallback(argc, "", true);
        return checkout(0);
    }

    std::string cmdName = strings::lower(argv[1]);
    Context ctx = newContext();

    std::string shortCmd = cmdName;
    // trim '-' from command name
    // expected: -help -> help 
    strings::trimPrefix(&shortCmd, "-");
    
    // allow all 4 types for help command:
    // $bin help
    // $bin h
    // $bin --help
    // $bin --h
    if (shortCmd == "help" || shortCmd == "h" || shortCmd == "-help" || shortCmd == "-h") {
        std::string subCmdName = "";
        if (argc > 2) {
            subCmdName = argv[2];
        }
        helpCallback(argc, strings::lower(subCmdName), true);
        return checkout(0);
    }

    // only allow shorters if they start with -
    if (strings::hasPrefix(cmdName, "-")) {
        // check if the entered command is a valid shorter and is present in shorters map
        if (shorters.find(shortCmd) != shorters.end()) {
            // replace shorter with original command name
            cmdName = shorters[shortCmd];
        }
    }

    // fallback to help command if entered command not found
    if (!exists(cmdName)) {
        helpFallback(cmdName);
        return checkout(0);
    }

    ctx.command = commands[cmdName];

    if (int errCode = parseCmdFlags(argc, argv, ctx.command->flags); errCode != 0) {
        helpCallback(3, cmdName, false);
        return checkout(errCode);
    };

    return checkout(ctx.command->callback(&ctx, argc, argv));
}

int CliApp::checkout(int exitCode) {
    return exitCode;
}

static int versionCallback(Context* ctx, int argc, char *argv[]) {
    std::cout << ctx->appName << " " << ctx->appVersion << std::endl;
    return 0;
}

CliApp::CliApp() {
    versionCommand->name = "version";
    versionCommand->shortDescription = "prints the current version of program.";
    versionCommand->description = "";
    versionCommand->callback = &versionCallback;
    versionCommand->shorter = "v";
    addCommand(versionCommand);
}