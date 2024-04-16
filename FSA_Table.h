#ifndef FSA_TABLE_H
#define FSA_TABLE_H
#include <string>
#include <map>
#include <iostream>
#include <array>
#include <tuple>
#include "Token.h"
//represents a indivdual state of a character in FSA table
struct FSA_State
{
    virtual ~FSA_State() {}
};
//dervied state to represent a connecting state in the FSA table
//ex: the first fsa state, a mid state,
// for digits is 2. This 2 is used to tell the lookahead state ptr
// in the Scanner to look at the second state of the next character
struct MidState : public FSA_State
{
    MidState(int nxt)
    {
        nextState = nxt;
    }
    int nextState;
};
//dervied state to represent a final state in the FSA table
//stores the token type of the final state so we know what token we generated in scanner
struct FinalState : public FSA_State
{
    FinalState(TokenType res)
    {
        tokenResult = res;
    }
    TokenType tokenResult;
};
//dervied state to represent a error state in the FSA table
//has unqiue error message to throw
struct ErrorState : public FSA_State
{
    ErrorState(std::string msg)
    {
        errorMsg = msg;

    }
    std::string errorMsg;
};

class FSA_Table
{

public:
    FSA_Table();//constructs table
    ~FSA_Table();//destroys table
    FSA_State* GetStateValue(char value, int stateIndex);//gets state of character from table

private:
    const static int AMOUNT_OF_STATES = 29; //amount of states each character has
    std::map<char, std::array<FSA_State*, AMOUNT_OF_STATES>> CharacterStates;//represents table, the key: each character. the value: an array of all their fsa states
    void BuildTable(); // builds table
    void AddNonUsedCharacterStates(); //adds all the different types of characters and their corresponding states to the table
    void AddLetterStates();//add letters a-zA-z to map. (all letters have same states of course)
    void AddDigitStates(); //add digits to map. (all digits have same states of course) 
    void AddStandardSingleLengthCharacterStates(); //adds similar single length characters and their states.
    void AddCharactersWithUniqueStates(); //adds characters that cause errors as they dont exist in the language
};

#endif