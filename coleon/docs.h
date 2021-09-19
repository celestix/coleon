#include <iostream>

std::string VERSION = "Coleon Version 1.0.0"
"\n\nColeon is a tool to manage copyrights of your source codes.";

std::string HELP_TEXT = "Coleon Copyright Solution 2021\n"
"\nUsage: coleon [option] path..."
"\nOptions:"
"\n  --help      Display help menu."
"\n  --version   Display Coleon version."
"\n  -c path...  Add custom copyright text file."
"\n  -f path...  Add copyright header to a file."
"\n  -r path...  Add copyright header to all files in a directory (Default path: './').";

int help(std::string option = "") {
    if (option == "") {
        std::cout << HELP_TEXT << std::endl;
    } else {
        std::cout << option << std::endl;
    }
    return 0;
}

int version() {
    std::cout << VERSION << std::endl;
    return 0;
}

