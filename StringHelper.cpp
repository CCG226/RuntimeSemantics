#include "StringHelper.h"
using namespace std;
//adds character c that is not whitespace to string parameter str and returns result
std::string StringHelper::AppendNonEmptyChar(std::string str, char c)
{
    if (c != ' ' && c != '\b' && c != '\t' && c != '\n' && c != '\v')
    {
        str += c;
    }
    return str;
}
//combines vector of strings into a string
string StringHelper::CombineStringsIntoString(vector<string> input)
{
    string res;
    for (int i = 0; static_cast<size_t>(i) < input.size();i++)
    {
        res += input[i] + '\n';
    }
    return res;
}
//converts string to vector of strings by new line
vector<string> StringHelper::SplitStringByNewLine(string input)
{
    stringstream strStream(input);
    string line;
    vector<string> res;

    while (getline(strStream, line, '\n'))
    {
        res.push_back(line);
    }

    return res;
}