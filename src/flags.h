#include <iostream>
#include <unordered_map>

// FlagType is an enum that represents the type of a flag.
// It can be either a string, a boolean, an integer or a size_t.
enum FlagType {
    FlagString,
    FlagBool,
    FlagInt,
    FlagSizeT
};

// BaseFlag is a base class for all flags.
// It contains a virtual function that returns the type of the flag.
class BaseFlag {
    public:
        // type returns the type of the flag.
        virtual FlagType type() = 0;
};

// BoolFlag is a class that represents a boolean flag.
// It contains a value and a required flag.
// The value is the value of the flag and the required flag is a boolean that indicates
// whether the flag is required or not.
class BoolFlag: public BaseFlag {
    public:
        // type returns the type of the flag.
        // In this case, it returns FlagBool.
        FlagType type();
        // value of the flag.
        bool value;
        // whether this flag is required or not.
        bool required;

        BoolFlag();
        BoolFlag(bool);
};

// StringFlag is a class that represents a string flag.
// It contains a value and a required flag.
// The value is the value of the flag and the required flag is a boolean that indicates
// whether the flag is required or not.
class StringFlag: public BaseFlag {
    public:
        // type returns the type of the flag.
        // In this case, it returns FlagString.
        FlagType type();
        // value of the flag.
        std::string value;
        // whether this flag is required or not.
        bool required;

        StringFlag();
        StringFlag(std::string);
};

// IntFlag is a class that represents an integer flag.
// It contains a value and a required flag.
// The value is the value of the flag and the required flag is a boolean that indicates
// whether the flag is required or not.
class IntFlag: public BaseFlag {
    public:
        // type returns the type of the flag.
        // In this case, it returns FlagInt.
        FlagType type();
        // value of the flag.
        int value;
        // whether this flag is required or not.
        bool required;

        IntFlag();
        IntFlag(int);
};

// SizeTFlag is a class that represents a size_t flag.
// It contains a value and a required flag.
// The value is the value of the flag and the required flag is a boolean that indicates
// whether the flag is required or not.
class SizeTFlag: public BaseFlag {
    public:
        // type returns the type of the flag.
        FlagType type();
        // value of the flag.
        size_t value;
        // whether this flag is required or not.
        bool required;
        // In this case, it returns FlagSizeT.

        SizeTFlag();
        SizeTFlag(size_t);
};