#include <iostream>
#include <stack>
#include <stdexcept>
#include "Token.h"
//Adapter for stack data structure for storing 
class SymbolStack
{
public:
    //constructor
    SymbolStack();
    //removal of token
    void Pop();
    //add token
    void Push(Token tk);
    //verify if token exists
    bool Find(Token tk);
    //is stack empty
    bool Empty();
    //top element returned
    Token Top();
    //size of stack
    size_t Size();
private:
    //adapts interface stack data structure of tokens 
    std::stack<Token> symbols;

};