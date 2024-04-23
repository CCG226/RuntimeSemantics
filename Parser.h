#ifndef PARSER_H
#define PARSER_H
#include <queue>
#include <string>
#include <sstream>
#include <iostream>
#include "Token.h"
#include "TerminalNode.h"
class Parser
{
public:
    //constructor
    Parser(std::queue<Token> inputTokens);
    //generates parse tree
    TerminalNode* Driver();
    //change token list data
    void ChangeInput(std::queue<Token> inputTokens);
    //prints parse tree via preorder traversal
    void PrintTree(TerminalNode* node, int level = 0);
    //clears tree data from root
    void Clear();

    TerminalNode* GetProgramNode();
private:
    //tree root (program terminal)
    TerminalNode* root;
    //queue of all tokens from scanner
    std::queue<Token> programTokens;
    //deletes a node
    void DeleteNode(TerminalNode* node);
    //reports error then exits
    void ErrorHandler(Token curTk, std::string terminal, std::string msg);
    //grammar terminals, each builds a node terminal and appends it to the tree with its token, child and label info
    TerminalNode* ProgramTerminal();
    TerminalNode* FuncTerminal();
    TerminalNode* BlockTerminal();
    TerminalNode* VarsTerminal();
    TerminalNode* ExprTerminal();
    TerminalNode* NTerminal();
    TerminalNode* ATerminal();
    TerminalNode* MTerminal();
    TerminalNode* RTerminal();
    TerminalNode* StatsTerminal();
    TerminalNode* MstatTerminal();
    TerminalNode* StatTerminal();
    TerminalNode* InTerminal();
    TerminalNode* OutTerminal();
    TerminalNode* IfTerminal();
    TerminalNode* PickTerminal();
    TerminalNode* PickbodyTerminal();
    TerminalNode* Loop1Terminal();
    TerminalNode* Loop2Terminal();
    TerminalNode* AssignTerminal();
    TerminalNode* ROTerminal();
    TerminalNode* LabelTerminal();
    TerminalNode* GotoTerminal();
};

#endif