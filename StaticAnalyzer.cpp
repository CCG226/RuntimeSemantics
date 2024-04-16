#include "StaticAnalyzer.h"
#include <iostream>
using namespace std;
//assign program parse tree root to ptr node programNode
StaticAnalyzer::StaticAnalyzer(TerminalNode* root)
{
    localVarCounter = 0;
    programNode = root;
}
//nullify ptr node
StaticAnalyzer::~StaticAnalyzer()
{
    programNode = nullptr;
}
//run static semantic analysis
void StaticAnalyzer::SemanticsDriver()
{
    TraverseTerminal(programNode);
}
//enters a program terminal and its children recursive to perform static analysis
void StaticAnalyzer::TraverseTerminal(TerminalNode* termNode)
{
    //flag that is raised after finishing global scope declarations
    static bool finishedAddingGlobalVariables = false;

    if (termNode == nullptr)
    { //child node doesnt exist, return 
        return;
    }
    //if entering block terminal
    if (termNode->label == BLOCK_DECLARATION)
    {
        //entering a new scope so exit previous scope and reset localVarCounter
        ExitLocalScope(localVarCounter);
        localVarCounter = 0;
        //if flag has not been raised and were entering a block terminal
         //then we must be done with global declarations so raise flag
        if (finishedAddingGlobalVariables == false)
        {
            finishedAddingGlobalVariables = true;
        }
    }
    //if we are in avariable declartion terminal (<vars>)
    if (termNode->label == VARIABLE_DECLARTIONS)
    {
        //if flag hasnt been raised we are declaring global variables
        if (!finishedAddingGlobalVariables)
        {
            VariableDecHandler(termNode->tk2, GLOBAL_SCOPE);
        }
        else
        {//if flag has been raised were are declaring local variables
        //and thus must track how many local variables we declared 
        //to know remeber how many variables are in this scope se we can remove them when exiting scope

            VariableDecHandler(termNode->tk2, LOCAL_SCOPE);
            localVarCounter++;
        }
    }
    //in ever node terminal check if terminal token 1 or 2 is a identifier and if that identifer is valid
    IdentiferUsageValidator(termNode->tk1);
    //ignore function names
    if (termNode->label != FUNC_DECLARATION)
    {
        IdentiferUsageValidator(termNode->tk2);
    }

    //recursival check child node terminals
    TraverseTerminal(termNode->child1);
    TraverseTerminal(termNode->child2);
    TraverseTerminal(termNode->child3);
    TraverseTerminal(termNode->child4);




}
//if identifier is found being used in program, check to ensure it exits in symbol table
void StaticAnalyzer::IdentiferUsageValidator(Token tk)
{
    if (tk.GetType() == Identifier && tk.GetVal() != "")
    {
        if (symbolStack.Find(tk) == false)
        {
            ErrorHandler(tk, "Undeclared Identifier " + tk.GetVal() + " used");
        }
    }
}
//checks to see if declared variable already exits(redeclaration error), else it adds new variable to stack
void StaticAnalyzer::VariableDecHandler(Token tk, std::string scopeName)
{
    if (symbolStack.Find(tk))
    {
        ErrorHandler(tk, scopeName + " variable \"" + tk.GetVal() + "\" has already been declared.");
    }
    else
    {
        symbolStack.Push(tk);
    }
}
//removes local variables from symbol stack when exiting scope block
void StaticAnalyzer::ExitLocalScope(int amountOfVars)
{
    for (int i = 0;i < amountOfVars;i++)
    {
        symbolStack.Pop();
    }
}
//error messages 
void StaticAnalyzer::ErrorHandler(Token tk, std::string msg)
{
    cout << "Static Semantics Analyzer Error: " << msg << endl;
    cout << "Token: " << tk.ToString() << endl;
    exit(1);
}