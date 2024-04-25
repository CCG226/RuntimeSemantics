#ifndef RUNTIMEANALYZER_H
#define RUNTIMEANALYZER_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "TerminalNode.h"
enum NameType
{ //used to determine if NameGenerator should generate a label name or variable name
    Variable,
    Label
};
class RuntimeAnalyzer
{
public:

    RuntimeAnalyzer(char fileType);//constructor, builds object and determines file name of asm output
    void SemanticsDriver(TerminalNode* root); //handles runtime semantics of program using parse tree
    void Reset(); //resets assembly output for reuse
    void ToAssembly();// stores string assembly output in a txt file
private:
    std::string NameGenerator(NameType type); //generates label/temp variable name 
    void InitializeAsmVariables();//appends variable initializations at end of assembly string
    void ErrorHandler(std::string msg);//reports errors
    std::string fileName;//output file name
    std::string output;//compiled UMSL ASM string
    std::string EvenOddLeftExprValue; //temp variable to track left expression value when using ... relational operator 
    std::string EvenOddRightExprValue;//temp variable to track right expression value when using ... relational operator 
    TerminalNode* funcPtr; //ptr to function node terminal to dynamically generate code of function on function call in asm
    std::string functionName;//tracks name of programs function
    std::vector<std::string> tempVariables;//list to track declared/generated variable names
    std::vector<std::string> tempLabels;//list to track declared/generated variable names

    //constant to represent node labels
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