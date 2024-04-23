#ifndef RUNTIMEANALYZER_H
#define RUNTIMEANALYZER_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "TerminalNode.h"
enum NameType
{
    Variable,
    Label
};
class RuntimeAnalyzer
{
public:

    RuntimeAnalyzer(char fileType);
    void SemanticsDriver(TerminalNode* root);
    void Reset();
    void ToAssembly();
private:
    std::string NameGenerator(NameType type);
    void InitializeAsmVariables();
    void ErrorHandler(std::string msg);
    std::string fileName;
    std::string output;
    std::string EvenOddLeftExprValue;
    std::string EvenOddRightExprValue;
    TerminalNode* funcPtr;
    std::string functionName;
    std::vector<std::string> tempVariables;
    std::vector<std::string> tempLabels;
    const std::string PROGRAM_LABEL = "Program";
    const std::string FUNC_LABEL = "Func";
    const std::string BLOCK_LABEL = "Block";
    const std::string VARS_LABEL = "Vars";
    const std::string EXPR_LABEL = "Expr";
    const std::string N_LABEL = "N";
    const std::string A_LABEL = "A";
    const std::string M_LABEL = "M";
    const std::string R_LABEL = "R";
    const std::string STATS_LABEL = "Stats";
    const std::string MSTAT_LABEL = "Mstat";
    const std::string STAT_LABEL = "Stat";
    const std::string IN_LABEL = "In";
    const std::string OUT_LABEL = "Out";
    const std::string IF_LABEL = "If";
    const std::string PICK_LABEL = "Pick";
    const std::string PICKBODY_LABEL = "Pickbody";
    const std::string LOOP1_LABEL = "Loop1";
    const std::string LOOP2_LABEL = "Loop2";
    const std::string ASSIGN_LABEL = "Assign";
    const std::string RO_LABEL = "RO";
    const std::string LABEL_LABEL = "Label";
    const std::string GOTO_LABEL = "Goto";


};

#endif