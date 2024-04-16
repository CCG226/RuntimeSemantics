#ifndef STATICANALYZER_H
#define STATICANALYZER_H
#include "TerminalNode.h"
#include "SymbolStack.h"
#include "Token.h"
class StaticAnalyzer
{
public:
    //nullify ptr node
    ~StaticAnalyzer();
    //assign program parse tree root to ptr node programNode
    StaticAnalyzer(TerminalNode* root);
    //run static semantic analysis
    void SemanticsDriver();
private:
    //constant string literals
    const std::string GLOBAL_SCOPE = "Global";
    const std::string LOCAL_SCOPE = "Local";
    const std::string VARIABLE_DECLARTIONS = "Vars";
    const std::string BLOCK_DECLARATION = "Block";
    const std::string FUNC_DECLARATION = "Func";
    //root node of a programs parse tree 
    TerminalNode* programNode;
    //symbol stack, for tracking variable scopes and detecting identifier miuse. (variable used in wrong scope/use of undeclared variable)
    SymbolStack symbolStack;
    //to track how many variables are declared in a scope, so we now how many variables to remove once exiting scope
    int localVarCounter;
    //enters a program terminal and its children recursive to perform static analysis
    void TraverseTerminal(TerminalNode* termNode);
    //checks to see if declared variable already exits(redeclaration error), else it adds new variable to stack
    void VariableDecHandler(Token tk, std::string scopeName);
    //removes local variables from symbol stack when exiting scope block
    void ExitLocalScope(int amountOfVars);
    //if identifier is found being used in program, check to ensure it exits in symbol table
    void IdentiferUsageValidator(Token tk);
    //error messages 
    void ErrorHandler(Token tk, std::string msg);

};

#endif