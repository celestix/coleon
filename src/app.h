#include <iostream>
#include <unordered_map>

#include "cmd.h"

// CliApp is the main class of the library responsible for parsing the command line arguments
// and executing the appropriate command.
// It provides various features like automatic help generation, automatic version generation,
// automatic flag parsing and more.
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
        // The name of the application.
        std::string name;

        // A short description of the application.
        std::string shortDescription;

        // A long description of the application.
        std::string description;

        // The version of the application.
        std::string version;

        // commandsHelp is a string that contains the help for all the commands.
        // It is built automatically by the library when CliApp::run is called
        std::string commandsHelp;
        
        // versionCommand is a command that is automatically added to the application
        Command *versionCommand = new Command;

        // addCommand adds a command to the application.
        bool addCommand(Command *handler);

        // run is a function that parses the command line arguments and executes the appropriate command.
        int run(int argc, char *argv[]);

    CliApp();
};