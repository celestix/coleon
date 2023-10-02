#include <iostream>

enum FlagType {
    FlagString,
    FlagBool,
    FlagInt,
    FlagSizeT
};

class BaseFlag {
    public:
        virtual FlagType type() = 0;
};

class BoolFlag: public BaseFlag {
    public:
        FlagType type();
        bool value;
        bool required;
        BoolFlag();
        BoolFlag(bool);
};

class StringFlag: public BaseFlag {
    public:
        FlagType type();
        std::string value;
        bool required;
        StringFlag();
        StringFlag(std::string);
};

class IntFlag: public BaseFlag {
    public:
        FlagType type();
        int value;
        bool required;
        IntFlag();
        IntFlag(int);
};

class SizeTFlag: public BaseFlag {
    public:
        FlagType type();
        size_t value;
        bool required;
        SizeTFlag();
        SizeTFlag(size_t);
};