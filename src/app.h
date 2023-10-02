#include <iostream>
#include <unordered_map>

#include "cmd.h"

class CliApp {
    private:
        size_t maxField = 0;

        std::unordered_map<std::string, Command*> commands;
        std::unordered_map<std::string, std::string> shorters;

        bool exists(std::string cmdName);
        Context newContext();
        
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
        
        Command *versionCommand = new Command;

        int run(int argc, char *argv[]);

        bool setCommand(Command *handler);

    CliApp();
};