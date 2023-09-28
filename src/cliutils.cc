#include <iostream>
#include <sstream>
#include <iomanip>

#include "cliutils.h"
#include "strutils.h"

#define __DEFAULT_HELP_ARGC 2

Context CliApp::newContext() {
    Context ctx;
    ctx.appName = name;
    ctx.appShortDescription = shortDescription;
    ctx.appDescription = description;
    ctx.appVersion = version;
    return ctx;
}

bool CliApp::setCommand(Command* command) {
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

void CliApp::helpCallback(int argc, char *argv[], bool general) {
    // $bin help
    if (argc <= 2) {
        if (general) {
            std::cout << name << "\n\n" << description << "\n" << commandsHelp << std::endl;
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
    std::cout << name << ": " << "'" << cmd << "'" << " is an invalid command.\n";
    helpCallback(__DEFAULT_HELP_ARGC, argv, false);
}

void CliApp::buildHelp() {
    std::stringstream s;
    for (const auto& cmd : commands) {
        s << "\n " << std::left << std::setw(maxField) << cmd.first << " : " << cmd.second->shortDescription;
    }
    commandsHelp = s.str();
}

int CliApp::run(int argc, char *argv[]) {
    // build help description
    buildHelp();

    if (argc == 1) {
        helpCallback(argc, argv, true);
        return checkout(0);
    }

    std::string cmd = strings::lower(argv[1]);
    Context ctx = newContext();

    // trim '--' from command name
    // expected: --help -> help 
    strings::trimPrefix(&cmd, "--");

    // replace shorter with original command name
    // only if command entered is a shorter
    if (shorters.find(cmd) != shorters.end()) {
        cmd = shorters[cmd];
    }

    if (cmd == "help" || cmd == "h") {
        helpCallback(argc, argv, true);
        return checkout(0);
    }

    // fallback to help command if entered command not found
    if (!exists(cmd)) {
        helpFallback(argv, cmd);
        return checkout(0);
    }
    ctx.command = commands[cmd];
    return checkout(ctx.command->callback(&ctx, argc, argv));
}

int CliApp::checkout(int exitCode) {
    return exitCode;
}

int versionCallback(Context* ctx, int argc, char *argv[]) {
    std::cout << ctx->appName << " " << ctx->appVersion << std::endl;
    return 0;
}

CliApp::CliApp() {
    versionCommand->name = "version";
    versionCommand->shortDescription = "prints the current version of program.";
    versionCommand->description = "";
    versionCommand->callback = &versionCallback;
    versionCommand->shorter = "v";
    setCommand(versionCommand);
}
