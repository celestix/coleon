#include <iostream>
#include <sstream>
#include "cliutils.h"
#include "strutils.h"

#define __DEFAULT_HELP_ARGC 2

Context *CliApp::newContext() {
    Context ctx;
    ctx.appName = name;
    ctx.appShortDescription = shortDescription;
    ctx.appDescription = description;
    ctx.appVersion = version;
    return &ctx;
}

bool CliApp::setCommand(Command* command) {
    if (command == NULL) {
        log << "CliApp: setCommand: Command NULL" << std::endl;
        return false;
    }
    log << "CliApp: setCommand: Added command [" << command->name << "]" << std::endl;
    commands[command->name] = command;
    return true;
}

bool CliApp::exists(std::string cmdName) {
    return (commands.find(cmdName) != commands.end());
}

void CliApp::enableVerbose() {
    verbose = true;
    log << "CliApp: Enabled verbose" << std::endl;
}

void CliApp::buildHelp() {
    std::stringstream s;
    for (const auto& cmd : commands) {
        s << "\n " << cmd.first << "\t: " << cmd.second->shortDescription;
    }
    commandsHelp = s.str();
}

int CliApp::run(int argc, char *argv[]) {
    log << "CliApp: Started" << std::endl;
    if (verbose) {
        log << "CliApp: Args-Count: " << argc << std::endl;
        log << "CliApp: Args-Value: ";
        for (int i = 0; i < argc; i++) {
            log << argv[i] << " ";
        }
        log << std::endl;
    }
    // build help description
    log << "CliApp: Building help section" << std::endl;
    buildHelp();
    log << "CliApp: Built help section" << std::endl;

    if (argc == 1) {
        log << "CliApp: No arg found, fallback to graceful help..." << std::endl;
        helpCallback(argc, argv, true);
        return checkout(0);
    }

    std::string cmd = strings::lower(argv[1]);
    Context *ctx = newContext();
    log << "CliApp: Created new context" << std::endl;

    // trim '--' from command name
    // expected: --help -> help 
    strings::trimPrefix(cmd, "--");

    // replace shorter with original command name
    // only if command entered is a shorter
    if (shorters.find(cmd) != shorters.end()) {
        cmd = shorters[cmd];
    }

    if (cmd == "help") {
        helpCallback(argc, argv, true);
        return checkout(0);
    }

    // fallback to help command if entered command not found
    if (!exists(cmd)) {
        log << "CliApp: No arg found, fallback to help..." << std::endl;
        helpFallback(argv, cmd);
        return checkout(0);
    }

    log << "CliApp: Calling command callback function..." << std::endl;
    return checkout(ctx->command->callback(ctx, argc, argv));
}

int CliApp::checkout(int exitCode) {
    if (!verbose) {
        // Clean log stream if not verbose
        delete &log;
    }
    return exitCode;
}

void CliApp::helpCallback(int argc, char *argv[], bool general) {
    // $bin help
    if (argc <= 2) {
        if (general) {
            std::cout << name << "\n\n" << description << "\n\n" << commandsHelp << std::endl;
        } else {
            std::cout << commandsHelp << std::endl;
        }
        return;
    }
    // $bin help $cmdName
    std::string cmdName = strings::lower(argv[2]);
    if (!exists(cmdName)) {
        helpFallback(argv, cmdName);
        return;
    }
    Command *cmd = commands[cmdName];
    std::cout << "Usage: " << argv[0] << " " << cmd->name << " <options>\n\n" << cmd->description << std::endl;
}

void CliApp::helpFallback(char *argv[], std::string cmd) {
    std::cout << name << ": " << "'" << cmd << "'" << " is an invalid command.\n\n";
    helpCallback(__DEFAULT_HELP_ARGC, argv, false);
}

int versionCallback(Context* ctx, int _, char**__) {
    std::cout << ctx->appName << " " << ctx->appVersion << std::endl;
    return 0;
}

CliApp::CliApp() {
    log << "CliApp: Created" << std::endl;
    Command versionCmd;
    versionCmd.name = "version";
    versionCmd.shortDescription = "prints the current version of program.";
    versionCmd.callback = &versionCallback;
    versionCmd.shorter = "v";
    setCommand(&versionCmd);
}
