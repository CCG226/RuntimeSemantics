#include "FSA_Table.h"
#include <string>
#include <map>

using namespace std;
//deconstructor of array element structs in 'CharacterStates' map
FSA_Table::~FSA_Table()
{
    for (auto& element : CharacterStates) {
        for (FSA_State* state : element.second) {
            delete state;
        }

    }
}
//constructor calls method to construct Table components
FSA_Table::FSA_Table()
{
    BuildTable();
}
//using character and state index, return that characters state at that index 
FSA_State* FSA_Table::GetStateValue(char value, int stateIndex)
{

    std::array<FSA_State*, AMOUNT_OF_STATES>& states = CharacterStates[value];

    return states[stateIndex];

}
//adds all the different types of characters and their corresponding states to the table
void FSA_Table::BuildTable()
{
    AddNonUsedCharacterStates();
    AddLetterStates();
    AddDigitStates();
    AddStandardSingleLengthCharacterStates();
    AddCharactersWithUniqueStates();
}
//add digits to map. (all digits have same states of course)
void  FSA_Table::AddDigitStates()
{
    const int AMOUNT_OF_DIGITS = 10;
    char asciiDigitsList[AMOUNT_OF_DIGITS] = {
        '0', '1', '2', '3', '4' ,'5', '6' ,'7' , '8' ,'9'
    };
    for (int i = 0; i < AMOUNT_OF_DIGITS;i++)
    {
        std::array<FSA_State*, AMOUNT_OF_STATES> fsaStates = {
             new MidState{2},
             new MidState{1},
             new MidState{2},
             new FinalState{OP_Assign},
             new FinalState{OP_Equal},
             new ErrorState{"Error: Illegal Letter Character During =!= Construction. ASCII Char - " + asciiDigitsList[i]},
             new FinalState{OP_Colon},
             new FinalState{OP_ColonEqual},
             new FinalState{OP_Plus},
             new FinalState{OP_Minus},
                 new FinalState{OP_Star},
             new FinalState{OP_ForwardSlash},
             new FinalState{OP_Carrot},
             new FinalState{Dot},
             new FinalState{LeftPara},
             new FinalState{RightPara},
             new FinalState{Comma},
          new FinalState{LeftCurl},
             new FinalState{RightCurl},
      new FinalState{Semicolon},
    new FinalState{LeftBracket},
             new FinalState{RightBracket},
               new FinalState{OP_LessThan},
                  new FinalState{OP_GreaterThan},
   new ErrorState{"Error: Illegal Letter Character During || Construction. ASCII Char - " + asciiDigitsList[i]},
            new FinalState{Op_Or},
          new ErrorState{"Error: Illegal Letter Character During && Construction. ASCII Char - " + asciiDigitsList[i]},
                  new FinalState{OP_And},
                    new FinalState{OP_NotEqual}
        };

        CharacterStates[asciiDigitsList[i]] = fsaStates;
    }
}
//add letters a-zA-z to map. (all letters have same states of course)
void FSA_Table::AddLetterStates()
{
    const int AMOUNT_OF_LETTERS = 52;
    char asciiLetterList[AMOUNT_OF_LETTERS] = {
          'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O',
           'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z','a', 'b', 'c',
            'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o',
           'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };
    for (int i = 0; i < AMOUNT_OF_LETTERS;i++)
    {
        std::array<FSA_State*, AMOUNT_OF_STATES> fsaStates = {
             new MidState{1},
             new MidState{1},
             new FinalState{Literal_Int},
             new FinalState{OP_Assign},
             new FinalState{OP_Equal},
             new ErrorState{"Error: Illegal Letter Character During =!= Construction. ASCII Char - " + asciiLetterList[i]},
             new FinalState{OP_Colon},
             new FinalState{OP_ColonEqual},
             new FinalState{OP_Plus},
             new FinalState{OP_Minus},
                 new FinalState{OP_Star},
             new FinalState{OP_ForwardSlash},
             new FinalState{OP_Carrot},
             new FinalState{Dot},
             new FinalState{LeftPara},
             new FinalState{RightPara},
             new FinalState{Comma},
       new FinalState{LeftCurl},
             new FinalState{RightCurl},
      new FinalState{Semicolon},
    new FinalState{LeftBracket},
             new FinalState{RightBracket},
               new FinalState{OP_LessThan},
                  new FinalState{OP_GreaterThan},
   new ErrorState{"Error: Illegal Letter Character During || Construction. ASCII Char - " + asciiLetterList[i]},
            new FinalState{Op_Or},
          new ErrorState{"Error: Illegal Letter Character During && Construction. ASCII Char - " + asciiLetterList[i]},
                  new FinalState{OP_And},
                    new FinalState{OP_NotEqual},

        };

        CharacterStates[asciiLetterList[i]] = fsaStates;
    }
}
//adds similar single length characters and their states.
//thier similiar becuase they all the same states except for the value stored in the element 0 MidState
void FSA_Table::AddStandardSingleLengthCharacterStates()
{

    const int AMOUNT_OF_OPERATORS_AND_DELIMITERS = 22;
    char asciiOpsAndDemsList[AMOUNT_OF_OPERATORS_AND_DELIMITERS] = { ' ','\b', '\t', '\n', '\v',
        '[',']','{','}', ':', ';', '<', '>', ',', '.', '/', '^', '*', '(', ')', '-', '+'
    };
    int valuesOfFirstStateOfChars[AMOUNT_OF_OPERATORS_AND_DELIMITERS] = {
      0, 0, 0, 0, 0, 20, 21, 17, 18,  6, 19, 22, 23, 16, 13, 11, 12, 10, 14, 15,9,8
    };
    for (int i = 0; i < AMOUNT_OF_OPERATORS_AND_DELIMITERS;i++)
    {
        std::array<FSA_State*, AMOUNT_OF_STATES> fsaStates = {
             new MidState(valuesOfFirstStateOfChars[i]),
             new FinalState{Identifier},
             new FinalState{Literal_Int},
             new FinalState{OP_Assign},
             new FinalState{OP_Equal},
             new ErrorState{"Error: Illegal Character During =!= Construction. ASCII Code - " + asciiOpsAndDemsList[i]},
             new FinalState{OP_Colon},
             new FinalState{OP_ColonEqual},
             new FinalState{OP_Plus},
             new FinalState{OP_Minus},
                 new FinalState{OP_Star},
             new FinalState{OP_ForwardSlash},
             new FinalState{OP_Carrot},
             new FinalState{Dot},
             new FinalState{LeftPara},
             new FinalState{RightPara},
             new FinalState{Comma},
       new FinalState{LeftCurl},
             new FinalState{RightCurl},
      new FinalState{Semicolon},
    new FinalState{LeftBracket},
             new FinalState{RightBracket},
               new FinalState{OP_LessThan},
                  new FinalState{OP_GreaterThan},
   new ErrorState{"Error: Illegal Character During || Construction. ASCII Code - " + asciiOpsAndDemsList[i]},
            new FinalState{Op_Or},
         new ErrorState{"Error: Illegal Character During && Construction. ASCII Code - " + asciiOpsAndDemsList[i]},
                  new FinalState{OP_And},
                    new FinalState{OP_NotEqual}
        };

        CharacterStates[asciiOpsAndDemsList[i]] = fsaStates;
    }

}
//adds characters that cause errors as they dont exist in the language
void FSA_Table::AddNonUsedCharacterStates()
{
    const int AMOUNT_OF_ESCAPE_CHARS = 38;
    char asciiChars[AMOUNT_OF_ESCAPE_CHARS] = {
        '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\a',
        '\f', '\r', '\x0E', '\x0F',
       '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17',
       '\x18', '\x19', '\x1A', '\x1B', '\x1C', '\x1D', '\x1E', '\x1F','\x7F',
        '\\', '\'', '"', '?',  '@', '#', '$', '%', '`', '~'
    };

    for (int i = 0; i < AMOUNT_OF_ESCAPE_CHARS;i++)
    {
        std::array<FSA_State*, AMOUNT_OF_STATES> fsaStates = {
             new ErrorState{"Error: IllegalCharacter. ASCII Code - " + std::to_string(static_cast<int>(asciiChars[i]))},
             new FinalState{Identifier},
             new FinalState{Literal_Int},
             new FinalState{OP_Assign},
             new FinalState{OP_Equal},
             new ErrorState{"Error: Illegal Character During =!= Construction. ASCII Code - " + std::to_string(static_cast<int>(asciiChars[i]))},
             new FinalState{OP_Colon},
             new FinalState{OP_ColonEqual},
             new FinalState{OP_Plus},
             new FinalState{OP_Minus},
                 new FinalState{OP_Star},
             new FinalState{OP_ForwardSlash},
             new FinalState{OP_Carrot},
             new FinalState{Dot},
             new FinalState{LeftPara},
             new FinalState{RightPara},
             new FinalState{Comma},
        new FinalState{LeftCurl},
             new FinalState{RightCurl},
      new FinalState{Semicolon},
    new FinalState{LeftBracket},
             new FinalState{RightBracket},
               new FinalState{OP_LessThan},
                  new FinalState{OP_GreaterThan},
   new ErrorState{"Error: Illegal Character During || Construction. ASCII Code - " + std::to_string(static_cast<int>(asciiChars[i]))},
            new FinalState{Op_Or},
         new ErrorState{"Error: Illegal Character During && Construction. ASCII Code - " + std::to_string(static_cast<int>(asciiChars[i]))},
                  new FinalState{OP_And},
                    new FinalState{OP_NotEqual}
        };

        CharacterStates[asciiChars[i]] = fsaStates;
    }


}
//adds states for characters taht generate unique token structures
// |, !, =, _, &, \0
void FSA_Table::AddCharactersWithUniqueStates()
{
    //for '|'
    std::array<FSA_State*, AMOUNT_OF_STATES> verticalBarStates = {
                 new MidState{24},
                 new FinalState{Identifier},
                 new FinalState{Literal_Int},
                 new FinalState{OP_Assign},
                 new FinalState{OP_Equal},
                  new ErrorState{"Error: Illegal Letter Character During =!= Construction. ASCII Char -  |"},
                 new FinalState{OP_Colon},
                 new FinalState{OP_ColonEqual},
                 new FinalState{OP_Plus},
                 new FinalState{OP_Minus},
                     new FinalState{OP_Star},
                 new FinalState{OP_ForwardSlash},
                 new FinalState{OP_Carrot},
                 new FinalState{Dot},
                 new FinalState{LeftPara},
                 new FinalState{RightPara},
                 new FinalState{Comma},
            new FinalState{LeftCurl},
             new FinalState{RightCurl},
      new FinalState{Semicolon},
    new FinalState{LeftBracket},
             new FinalState{RightBracket},
                   new FinalState{OP_LessThan},
                      new FinalState{OP_GreaterThan},
       new MidState{25},
                new FinalState{Op_Or},
              new ErrorState{"Error: Illegal Letter Character During && Construction. ASCII Char -  |"},
                      new FinalState{OP_And},
                        new FinalState{OP_NotEqual}
    };

    CharacterStates['|'] = verticalBarStates;

    //for  '!'
    std::array<FSA_State*, AMOUNT_OF_STATES> exclamationStates = {
                new ErrorState{"Error: Illegal Character . ASCII Char -  !"},
                new FinalState{Identifier},
                new FinalState{Literal_Int},
                new MidState{5},
                new FinalState{OP_Equal},
                 new ErrorState{"Error: Illegal Letter Character During =!= Construction. ASCII Char -  !"},
                new FinalState{OP_Colon},
                new FinalState{OP_ColonEqual},
                new FinalState{OP_Plus},
                new FinalState{OP_Minus},
                    new FinalState{OP_Star},
                new FinalState{OP_ForwardSlash},
                new FinalState{OP_Carrot},
                new FinalState{Dot},
                new FinalState{LeftPara},
                new FinalState{RightPara},
                new FinalState{Comma},
           new FinalState{LeftCurl},
             new FinalState{RightCurl},
      new FinalState{Semicolon},
    new FinalState{LeftBracket},
             new FinalState{RightBracket},
                  new FinalState{OP_LessThan},
                     new FinalState{OP_GreaterThan},
   new ErrorState{"Error: Illegal Letter Character During || Construction. ASCII Char -  !"},
               new FinalState{Op_Or},
             new ErrorState{"Error: Illegal Letter Character During && Construction. ASCII Char -  !"},
                     new FinalState{OP_And},
                       new FinalState{OP_NotEqual}
    };

    CharacterStates['!'] = exclamationStates;
    //for  '='
    std::array<FSA_State*, AMOUNT_OF_STATES> equalStates = {
                new MidState{3},
                new FinalState{Identifier},
                new FinalState{Literal_Int},
                 new MidState{4},
                new FinalState{OP_Equal},
               new MidState{28},
          new MidState{7},
                new FinalState{OP_ColonEqual},
                new FinalState{OP_Plus},
                new FinalState{OP_Minus},
                    new FinalState{OP_Star},
                new FinalState{OP_ForwardSlash},
                new FinalState{OP_Carrot},
                new FinalState{Dot},
                new FinalState{LeftPara},
                new FinalState{RightPara},
                new FinalState{Comma},
             new FinalState{LeftCurl},
             new FinalState{RightCurl},
      new FinalState{Semicolon},
    new FinalState{LeftBracket},
             new FinalState{RightBracket},
                  new FinalState{OP_LessThan},
                     new FinalState{OP_GreaterThan},
   new ErrorState{"Error: Illegal Letter Character During || Construction. ASCII Char - ="},
               new FinalState{Op_Or},
             new ErrorState{"Error: Illegal Letter Character During && Construction. ASCII Char -  ="},
                     new FinalState{OP_And},
                       new FinalState{OP_NotEqual}
    };

    CharacterStates['='] = equalStates;
    //for  '_'
    std::array<FSA_State*, AMOUNT_OF_STATES> underscoreStates = {
                    new ErrorState{"Error: Illegal Character . ASCII Char -  _"},
                    new MidState{1},
                    new FinalState{Literal_Int},
                    new FinalState{OP_Assign},
                    new FinalState{OP_Equal},
                     new ErrorState{"Error: Illegal Letter Character During =!= Construction. ASCII Char -  _"},
                    new FinalState{OP_Colon},
                    new FinalState{OP_ColonEqual},
                    new FinalState{OP_Plus},
                    new FinalState{OP_Minus},
                        new FinalState{OP_Star},
                    new FinalState{OP_ForwardSlash},
                    new FinalState{OP_Carrot},
                    new FinalState{Dot},
                    new FinalState{LeftPara},
                    new FinalState{RightPara},
                    new FinalState{Comma},
               new FinalState{LeftCurl},
             new FinalState{RightCurl},
      new FinalState{Semicolon},
    new FinalState{LeftBracket},
             new FinalState{RightBracket},
                      new FinalState{OP_LessThan},
                         new FinalState{OP_GreaterThan},
                          new ErrorState{"Error: Illegal Letter Character During || Construction. ASCII Char -  _"},
                   new FinalState{Op_Or},
                 new ErrorState{"Error: Illegal Letter Character During && Construction. ASCII Char -  _"},
                         new FinalState{OP_And},
                           new FinalState{OP_NotEqual}
    };

    CharacterStates['_'] = underscoreStates;

    //for  '&'
    std::array<FSA_State*, AMOUNT_OF_STATES> andStates = {
                new MidState{26},
                new FinalState{Identifier},
                new FinalState{Literal_Int},
                new FinalState{OP_Assign},
                new FinalState{OP_Equal},
                 new ErrorState{"Error: Illegal Letter Character During =!= Construction. ASCII Char -  &"},
                new FinalState{OP_Colon},
                new FinalState{OP_ColonEqual},
                new FinalState{OP_Plus},
                new FinalState{OP_Minus},
                    new FinalState{OP_Star},
                new FinalState{OP_ForwardSlash},
                new FinalState{OP_Carrot},
                new FinalState{Dot},
                new FinalState{LeftPara},
                new FinalState{RightPara},
                new FinalState{Comma},
            new FinalState{LeftCurl},
             new FinalState{RightCurl},
      new FinalState{Semicolon},
    new FinalState{LeftBracket},
             new FinalState{RightBracket},
                  new FinalState{OP_LessThan},
                     new FinalState{OP_GreaterThan},
new ErrorState{"Error: Illegal Letter Character During || Construction. ASCII Char -  &"},
               new FinalState{Op_Or},
             new MidState{27},
                     new FinalState{OP_And},
                       new FinalState{OP_NotEqual}
    };

    CharacterStates['&'] = andStates;
    //for  'EOF'
    std::array<FSA_State*, AMOUNT_OF_STATES> eofStates = {
                new FinalState{Eof},
                new FinalState{Identifier},
                new FinalState{Literal_Int},
                new FinalState{OP_Assign},
                new FinalState{OP_Equal},
                 new ErrorState{"Error: Illegal Letter Character During =!= Construction. ASCII Char -  &"},
                new FinalState{OP_Colon},
                new FinalState{OP_ColonEqual},
                new FinalState{OP_Plus},
                new FinalState{OP_Minus},
                    new FinalState{OP_Star},
                new FinalState{OP_ForwardSlash},
                new FinalState{OP_Carrot},
                new FinalState{Dot},
                new FinalState{LeftPara},
                new FinalState{RightPara},
                new FinalState{Comma},
            new FinalState{LeftCurl},
             new FinalState{RightCurl},
      new FinalState{Semicolon},
    new FinalState{LeftBracket},
             new FinalState{RightBracket},
                  new FinalState{OP_LessThan},
                     new FinalState{OP_GreaterThan},
new ErrorState{"Error: Illegal Letter Character During || Construction. ASCII Char -  &"},
               new FinalState{Op_Or},
             new MidState{27},
                     new FinalState{OP_And},
                       new FinalState{OP_NotEqual}
    };

    CharacterStates['\0'] = eofStates;
}