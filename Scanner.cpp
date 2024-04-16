#include "Scanner.h"
#include "StringHelper.h"
#include <iostream>
using namespace std;
//constructor, data is string to scan for tokens
Scanner::Scanner(string data)
{
    input = data;

    CommentRemover();

    nextCharacterPtr = input[0];
    nextStatePtr = 0;
    lineCharacterCounter = 0;
    lineCounter = 0;
    inputIndex = 0;
}
//scanner driver
queue<Token> Scanner::Driver()
{
    queue<Token> res;

    Token token;

    do
    {
        token = GenerateNextToken();

        res.push(token);

    } while (token.isEOF() == false);

    return res;
}
//preprocessor function that removes comments
void Scanner::CommentRemover()
{

    vector<string> inputSplitByLine = StringHelper::SplitStringByNewLine(input);
    vector<string> inputLinesWithoutComments;
    for (int i = 0; static_cast<size_t>(i) < inputSplitByLine.size(); i++) {

        size_t commentPos = inputSplitByLine[i].find("//");
        if (commentPos != std::string::npos) {

            inputLinesWithoutComments.push_back(inputSplitByLine[i].substr(0, commentPos));

        }
        else {

            inputLinesWithoutComments.push_back(inputSplitByLine[i]);
        }
    }

    input = StringHelper::CombineStringsIntoString(inputLinesWithoutComments);

}
//increments inputIndex, stores next char in string in nextCharacterPtr, 
void Scanner::GetNextChar()
{

    if (nextCharacterPtr == '\n')
    {
        CountNewLine();
    }

    inputIndex++;

    nextCharacterPtr = input[inputIndex];

}
//counts new line if next char is \n
void Scanner::CountNewLine()
{
    lineCharacterCounter = 0;
    lineCounter++;
}
// calcuates start position of token value on a line using lineCharacterCounter and string length()
int Scanner::CalcStartPositionOfToken(std::string str)
{
    const int SINGLE_LENGTH_TOKEN = 1;

    if (str.length() > SINGLE_LENGTH_TOKEN)
    {
        int backTrace = str.length() - 1;
        return lineCharacterCounter - backTrace;
    }
    else
    {
        return lineCharacterCounter;
    }
}
//creates new token after final state is returned from table
Token Scanner::Finalizer(std::string str, TokenType tk)
{

    int initTokenPos = CalcStartPositionOfToken(str);

    Token res(tk, str, lineCounter, initTokenPos);

    return res;
}
//generates a single token from string input
Token Scanner::GenerateNextToken()
{

    Token result;
    string stringBuilder;
    bool isFinal = false;
    while (isFinal == false)
    {
        FSA_State* curState = fsaTable.GetStateValue(nextCharacterPtr, nextStatePtr);

        if (auto errorState = dynamic_cast<ErrorState*>(curState))
        {

            ErrorHandler(errorState->errorMsg);
        }
        else if (auto finalState = dynamic_cast<FinalState*>(curState))
        {

            result = Finalizer(stringBuilder, finalState->tokenResult);
            isFinal = true;
        }
        else if (auto midState = dynamic_cast<MidState*>(curState))
        {

            stringBuilder = StringHelper::AppendNonEmptyChar(stringBuilder, nextCharacterPtr);

            nextStatePtr = midState->nextState;

            lineCharacterCounter++;

            GetNextChar();

        }
        else
        {
            ErrorHandler("ERROR: Unknown State Type");
        }

    }

    nextStatePtr = 0;

    return result;



}
//handles scanner errors
void Scanner::ErrorHandler(string msg)
{
    cout << "Scanner :: Error State occurred. At state: " + to_string(nextStatePtr) +
        ". For ASCII character value: " +
        to_string(static_cast<int>(nextCharacterPtr)) + ". At line number: " +
        to_string(lineCounter) + ". At character number: " + to_string(lineCharacterCounter) << endl;

    throw runtime_error(msg);
}

/*
    char charList[] = {
     '\0', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\a',
     '\b', '\t', '\n', '\v', '\f', '\r', '\x0E', '\x0F',
     '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17',
     '\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', '\x1E', '\x1F',
     ' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
     '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?',
     '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
     'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\\', ']', '^', '_',
     '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
     'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', '\x7F'
    };
*/