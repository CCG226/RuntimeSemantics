#include "SymbolStack.h"
using namespace std;
//constructor
SymbolStack::SymbolStack() {}

//add token
void SymbolStack::Push(Token element)
{
    const int MAX_LIMIT = 250;
    if (symbols.size() >= MAX_LIMIT)
    {
        throw runtime_error("Invalid SymbolStack Action: Max size limit (250) for SymbolStack has been reached during Push operation!");
    }
    symbols.push(element);
}
//removal of token
void SymbolStack::Pop()
{
    if (symbols.empty())
    {
        throw runtime_error("Invalid SymbolStack Action: Tried to remove top token from stack with Pop, but stack is empty!");
    }
    symbols.pop();
}
//size of stack
size_t SymbolStack::Size()
{
    return symbols.size();
}
//top element returned
Token SymbolStack::Top()
{
    if (symbols.empty())
    {
        throw runtime_error("Invalid SymbolStack Action: Tried to access top token from stack with Top, but stack is empty!");
    }
    return symbols.top();
}
//verify if token exists
bool SymbolStack::Find(Token tk)
{
    std::stack<Token> copy(symbols);

    while (copy.empty() == false)
    {
        if (copy.top().GetVal() == tk.GetVal())
        {
            return true;
        }
        copy.pop();
    }
    return false;
}
//is stack empty
bool SymbolStack::Empty()
{
    return symbols.empty();
}