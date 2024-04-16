#ifndef RUNTIMEANALYZER_H
#define RUNTIMEANALYZER_H
#include <string>
#include <vector>
enum NameType
{
    Variable,
    Label
};
class RuntimeAnalyzer
{
public:
    RuntimeAnalyzer(char fileType);
    void SemanticsDriver();

private:
    std::string NameGenerator(NameType type);
    void ErrorHandler(std::string msg);
    std::string fileName;
    std::string output;


};

#endif