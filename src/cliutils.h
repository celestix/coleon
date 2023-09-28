#include <iostream>
#include <unordered_map>
#include "bufutils.h"

struct Context;

#define __HANDLER_CALLBACK int(*callback)(Context *ctx, int argc, char *argv[])

struct Command {
    std::string name;
    std::string shortDescription;
    std::string description;
    std::string shorter;
    
    __HANDLER_CALLBACK;
};

struct Context {
    std::string appName;
    std::string appShortDescription;
    std::string appDescription;
    std::string appVersion;

    Command *command;
};

class CliApp {
    private:
    bool verbose;

    std::unordered_map<std::string, Command*> commands;
    std::unordered_map<std::string, std::string> shorters;

    bool exists(std::string cmdName);
    Context* newContext();
    
    void buildHelp();

    void helpCallback(int, char**, bool);
    void helpFallback(char**, std::string);

    int checkout(int);

    public:
    std::string name;
    std::string shortDescription;
    std::string description;
    std::string version;
    std::string commandsHelp;

    std::ostream& log = verbose ? std::cout : *(new std::ostream(new Discard));

    int run(int argc, char *argv[]);
    void enableVerbose();

    bool setCommand(Command *handler);

    CliApp();
};
