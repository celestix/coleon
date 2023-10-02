#include <iostream>
#include <unordered_map>

#include "flags.h"

struct Context;

#define __HANDLER_CALLBACK int(*callback)(Context *ctx, int argc, char *argv[])

struct Command {
    std::string name;
    std::string shortDescription;
    std::string description;
    std::string shorter;

    __HANDLER_CALLBACK;
    void addFlag(std::string flagName, BaseFlag* flag);

    private:
    std::unordered_map<std::string, BaseFlag*> flags;
};

struct Context {
    std::string appName;
    std::string appShortDescription;
    std::string appDescription;
    std::string appVersion;

    Command *command;
};
