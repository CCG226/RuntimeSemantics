#ifndef SCANNER_H
#define SCANNER_H
#include "FSA_Table.h"
#include "Token.h"
#include <vector>
#include <string>
#include <queue>
class Scanner
{
public:

    Scanner(std::string data); //constructor, data is string to scan for tokens
    std::queue<Token> Driver();

private:
    std::string input; //data parameter from constructor
    int inputIndex; //keeps track of our index in input string
    char nextCharacterPtr;//stores next character to look up at in table
    int nextStatePtr; //stores next state of next character to look up at in table
    int lineCounter; //counts new lines in input string (debugging)
    int lineCharacterCounter;//counts each character on a line in input string, resets each line (debugging)
    FSA_Table fsaTable; //our fsa table
    Token GenerateNextToken();//generates a single token from string input
    void CommentRemover();//preprocessor function that removes comments
    void ErrorHandler(std::string msg); //handles scanner errors
    Token Finalizer(std::string str, TokenType tk); //creates new token after final state is returned from table
    void GetNextChar(); //increments inputIndex, stores next char in string in nextCharacterPtr, 
    void CountNewLine();//counts new line if next char is \n
    int CalcStartPositionOfToken(std::string str); // calcuates start position of token value on a line using lineCharacterCounter and string length()
};

#endif