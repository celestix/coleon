#include <fstream>
#include <filesystem>
#include <string>

namespace strings {
    std::string toLower(std::string s) {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }
    std::string toUpper(std::string s) {
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        return s;
    }
}

namespace file {
    std::string read(std::string fname) {
        std::fstream f;
        std::string s;
        f.open(fname, std::ios::in);
        if (!f) {
            std::cout << fname + " could not be found!" << std::endl;
        } else {
            while (!f.eof()) {
                std::string st; getline(f, st);
                s = s + st + "\n";
            }
        }
        f.close();
        return s;
    }
    int write(std::string fname, std::string cfname = "copyright.txt") {
        // 0 = done
        // 1 = not written
        // 2 = copyright file not found
        std::string copyright = read(cfname);
        if (copyright == "") {
            return 2;
        }
        copyright = copyright + "\n" + read(fname);
        std::fstream f;
        f.open(fname, std::ios::out);
        if (!f) {
            std::cout << fname + " could not be written!" << std::endl;
            return 1;
        }
        else {
            f << copyright << std::endl;
        }
        f.close();
        return 0;
    }
    void writeall(std::string path = "./", std::string cfname = "copyright.txt") {
        try {
            bool done = false;
            for (const auto& entry : std::filesystem::directory_iterator(path)) {
                int status_code = write(entry.path().string(), cfname);
                if (status_code == 1) {
                    continue;
                }
                else if (status_code == 2) {
                    break;
                }
                done = true;
            }
            if (done) {
                std::cout << "Successfully added copyright header to all files in directory with path: '" + path + "'" << std::endl;
            }
            return;
        }
        catch (...) {
            std::cout << "Failed to open: '" + path + "', make sure it exists!";
            return;
        }
    }
}
