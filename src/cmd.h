#include <iostream>
#include <unordered_map>

#include "flags.h"

struct Context;

// __HANDLER_CALLBACK is a macro that represents the callback function of a command.
#define __HANDLER_CALLBACK int(*callback)(Context *ctx, int argc, char *argv[])

// Command is a struct that represents a command that can be executed by the application.
// It contains the command name, a short description, a long description and a callback function.
// The callback function is called when the command is executed.
// The callback function receives a Context struct, the number of arguments and the arguments themselves.
struct Command {
    // The name of the command.
    std::string name;

    // A short description of the command.
    std::string shortDescription;
    
    // A long description of the command.
    std::string description;

    // A shorter alias of the command (Optional).
    // Note: The shorter alias will only be parsed if it starts with double dashes.
    // Example: If the shorter alias is "t", then the command will be parsed if the user
    //         executes the command like this: $bin --t
    std::string shorter;

    // The callback function of the command.
    __HANDLER_CALLBACK;

    // addFlag adds a flag to the command.
    void addFlag(std::string flagName, BaseFlag* flag);

    BaseFlag* getFlag(std::string flagName);

    std::unordered_map<std::string, BaseFlag*> flags;
    int maxField = 0;
};

// Context is a struct that represents the context of the application.
// It contains the application name, a short description, a long description and the application version.
// It also contains a pointer to the command that is being executed.
struct Context {
    // The name of the application.
    std::string appName;
    // A short description of the application.
    std::string appShortDescription;
    // A long description of the application.
    std::string appDescription;
    // The version of the application.
    std::string appVersion;

    // The command that is being executed. 
    Command *command;
};
