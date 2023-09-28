#include<streambuf>

class Discard : public std::streambuf {
public:
    int overflow(int c) override {
        return c;
    }
};