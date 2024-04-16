#ifndef STRINGHELPER_H
#define STRINGHELPER_H
#include <vector>
#include <string>
#include <sstream>
class StringHelper
{
public:
    //adds character c that is not whitespace to string parameter str and returns result
    static std::string AppendNonEmptyChar(std::string str, char c);
    //converts string to vector of strings by new line
    static std::vector<std::string> SplitStringByNewLine(std::string input);
    //combines vector of strings into a string
    static std::string CombineStringsIntoString(std::vector<std::string> input);

};

#endif