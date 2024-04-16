#ifndef TERMINALNODE_H
#define TERMINALNODE_H
#include <string>
#include "Token.h"
class TerminalNode
{
public:
    TerminalNode(std::string name);
    std::string label;
    Token tk1;
    Token tk2;
    Token tk3;
    Token tk4;
    Token tk5;
    TerminalNode* child1;
    TerminalNode* child2;
    TerminalNode* child3;
    TerminalNode* child4;

};

#endif