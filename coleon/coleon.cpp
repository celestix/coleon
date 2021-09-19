#include "colion.h"

int main(int argc, char *argv[]) {
    std::string cheader = "copyright.txt";
    std::string path = "";
    std::string dir = "";
    int currentval = 0;
    if (argc >= 2) {
        std::string mode = strings::toLower(argv[1]);
        if (mode == "--version") {
            return version();
        } else if (mode == "--help" || mode == "help") {
            return help();
        }
        for (int i = 2; i <= argc; ++i) {
            if (i == currentval) {
                continue;
            }
            mode = strings::toLower(argv[i-1]);
            if (mode == "-r") {
                if (path != "" || strings::toLower(argv[i]) == "-f") {
                    std::cout << "Can't use '-f' and '-r' options simultaneously!" << std::endl;
                    return 0;
                }
                if (argc < i) {
                    dir = "./";
                    continue;
                }
                dir = argv[i];
                currentval = i + 1;
            } else if (mode == "-f") {
                if (dir != "" || strings::toLower(argv[i]) == "-r") {
                    std::cout << "Can't use '-f' and '-r' options simultaneously!" << std::endl;
                    return 0;
                }
                if (argc < i) {
                    std::cout << "File was not provided. See 'coleon --help'" << std::endl;
                    return 0;
                }
                path = argv[i];
                currentval = i + 1;
            } else if (mode == "-c") {
                if (argc < i) {
                    std::cout << "Used option '-c' but have not provided path of copyright file! See 'coleon --help'" << std::endl;
                    return 0;
                }
                cheader = argv[i];
                currentval = i + 1;
            } else {
                std::cout << "Invalid option: '" + mode + "', See 'coleon --help'" << std::endl;
                return 0;
            }
        }
        if (path == "" && dir == "") {
            return 0;
        } else if (path != "") {
            if (file::write(path, cheader) == 0) {
                std::cout << "Successfully added copyright header to file with path: '" + path + "'" << std::endl;
            }
        } else {
            file::writeall(dir, cheader);
        }
        return 0;


        /*else if (mode == "read") {
            if (argc <= 2) {
                std::cout << "You need to provide me a file to read." << std::endl;
                return 0;
            }
            std::string fdata = file::read(argv[2]);
            std::cout << fdata;
            return 0;
        }
        else if (mode == "write") {
            if (argc <= 2) {
                std::cout << "You need to provide me a file to write." << std::endl;
                return 0;
            }
            file::write(argv[2]);
            return 0;
        }
        else if (mode == "writeall") {
            std::string path = argv[2];
            if (argc <= 2) {
                path = "./";
            }
            file::writeall(path);
            return 0;
        }*/

    }
    std::cout << "You need to provide an argument." << std::endl << "check 'coleon --help'";
    return 0;
}

