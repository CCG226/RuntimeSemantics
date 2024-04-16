#include "RuntimeAnalyzer.h"
#include <iostream>
using namespace std;

RuntimeAnalyzer::RuntimeAnalyzer(char fileType)
{
    if (fileType == 'F')
    {
        fileName = "file.asm";
    }
    else if (fileType == 'K')
    {
        fileName = "kb.asm";
    }
    else
    {
        ErrorHandler("Unknown parameter for fileType determination, character must be either K for keyboard or F for file.");
    }
}
std::string RuntimeAnalyzer::NameGenerator(NameType type)
{
    static int varCounter = 0;
    static int labelCounter = 0;
    string res = "";
    if (type == Variable)
    {
        res = "V" + to_string(varCounter);
        varCounter++;
    }
    else if (type == Label)
    {
        res = "L" + to_string(labelCounter);
        labelCounter++;
    }
    else
    {
        ErrorHandler("Unkown Name Type during name generation");
    }
    cout << res << endl;
    return res;
}

void RuntimeAnalyzer::ErrorHandler(string msg)
{
    cout << "Runtime Semantics Analyzer Error: " << msg << endl;
    exit(1);
}
void RuntimeAnalyzer::SemanticsDriver()
{
    output = "";
    NameGenerator(Variable);
    NameGenerator(Label);
    NameGenerator(Variable);
    NameGenerator(Variable);
    NameGenerator(Label);
    NameGenerator(Label);
    NameGenerator(Variable);
    NameGenerator(Variable);
}