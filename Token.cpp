#include "Token.h"
#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;
//token constructor with token type, string value, line num, char num params

Token::Token(TokenType type, std::string value, int lineNumber, int charNumber)
{
    if (type == Eof)
    {//prevent EOF token value from just being empty
        value = "EOF";
    }

    if (type == Identifier)
    {//if value is keyword, change type to identifier
        IdentifierValidator(value);
        if (IsKeyword(value))
        {
            type = KeywordStringToToken(value);
        }
    }
    this->type = type;

    this->value = value;

    this->lineLocation = lineNumber;

    this->charLocation = charNumber;


}
std::string Token::GetVal()
{
    return this->value;
}
TokenType Token::GetType()
{
    return this->type;
}
//checks if a string value is a keyword
bool Token::IsKeyword(std::string str)
{
    const int KW_AMOUNT = 17;
    string keywords[KW_AMOUNT] = { "start", "stop", "while", "repeat", "until", "label", "return", "cin", "cout", "tape", "jump", "if", "then", "pick", "create", "set", "func" };

    for (int i = 0; i < KW_AMOUNT;i++)
    {
        if (str == keywords[i])
        {
            return true;
        }
    }
    return false;
}
//ensures Identifier doesnt violate length constraints
void Token::IdentifierValidator(string str)
{
    const int MAX_ID_LENGTH = 32;

    if (str.length() > MAX_ID_LENGTH)
    {
        throw runtime_error("Invalid Identifier: " + str + "  Length Greater Than Limit 32!");
    }
}
//sees if Token is EOF
bool Token::isEOF()
{
    if (type == Eof)
    {
        return true;
    }
    return false;
}
//assign Token to Token
Token& Token::operator=(const Token& other) {
    if (this != &other) {

        type = other.type;
        value = other.value;
        lineLocation = other.lineLocation;
        charLocation = other.charLocation;
    }
    return *this;
}
//converts token data to string 
string Token::ToString()
{

    return "Token =>  Type: " + StringifyTokenType() + "  Value: " + value + "  Line Number: " + std::to_string(lineLocation + 1) + "  Character Number: " + std::to_string(charLocation) + "\n";
}
//turns 'type', the TokenType enum to string
string Token::StringifyTokenType()
{
    string str = "";
    switch (this->type)
    {
    case (Eof):
        str = "EOF";
        break;
    case (Identifier):
        str = "Identifier";
        break;
    case (Literal_Int):
        str = "Int Literal";
        break;
    case (KW_start):
        str = "Keyword start";
        break;
    case (KW_stop):
        str = "Keyword stop";
        break;
    case (KW_while):
        str = "Keyword while";
        break;
    case (KW_repeat):
        str = "Keyword repeat";
        break;
    case (KW_until):
        str = "Keyword until";
        break;
    case (KW_label):
        str = "Keyword label";
        break;
    case (KW_return):
        str = "Keyword return";
        break;
    case (KW_cin):
        str = "Keyword cin";
        break;
    case (KW_cout):
        str = "Keyword cout";
        break;
    case (KW_tape):
        str = "Keyword tape";
        break;
    case (KW_jump):
        str = "Keyword jump";
        break;
    case (KW_if):
        str = "Keyword if";
        break;
    case (KW_then):
        str = "Keyword then";
        break;
    case (KW_pick):
        str = "Keyword pick";
        break;
    case (KW_create):
        str = "Keyword create";
        break;
    case (KW_set):
        str = "Keyword set";
        break;
    case (KW_func):
        str = "Keyword func";
        break;
    case (OP_Assign):
        str = "Operator Assignment";
        break;
    case (OP_LessThan):
        str = "Operator Less Than";
        break;
    case (OP_GreaterThan):
        str = "Operator Greater Than";
        break;
    case (OP_Equal):
        str = "Operator Equal";
        break;
    case (OP_NotEqual):
        str = "Operator Not Equal";
        break;
    case (OP_Colon):
        str = "Operator Colon";
        break;
    case (OP_ColonEqual):
        str = "Operator Colon Equal";
        break;
    case (OP_Plus):
        str = "Operator Add";
        break;
    case (OP_Minus):
        str = "Operator Subtract";
        break;
    case (OP_Star):
        str = "Operator Multiply";
        break;
    case (OP_ForwardSlash):
        str = "Operator Divide";
        break;
    case (OP_Carrot):
        str = "Operator Exponent";
        break;
    case (Dot):
        str = "Dot";
        break;
    case (LeftPara):
        str = "Left Parenthesis";
        break;
    case (RightPara):
        str = "Right Parenthesis";
        break;
    case (Comma):
        str = "Comma";
        break;
    case (LeftCurl):
        str = "Left Curly Brace";
        break;
    case (RightCurl):
        str = "Right Curly Brace";
        break;
    case (Semicolon):
        str = "Semicolon";
        break;
    case (LeftBracket):
        str = "Left Bracket";
        break;
    case (RightBracket):
        str = "Right Bracket";
        break;
    case (Op_Or):
        str = "Operator Or";
        break;
    case (OP_And):
        str = "Operator And";
        break;
    default:
        cout << "Unkown Token Type";
        exit(1);
        break;
    }
    return str;
}
//takes keyword string and returns corresponding TokenType enum
TokenType Token::KeywordStringToToken(std::string str)
{
    TokenType res;
    if (str == "start")
    {
        res = KW_start;
    }
    if (str == "stop")
    {
        res = KW_stop;
    }
    if (str == "while")
    {
        res = KW_while;
    }
    if (str == "repeat")
    {
        res = KW_repeat;
    }
    if (str == "until")
    {
        res = KW_until;
    }
    if (str == "label")
    {
        res = KW_label;
    }
    if (str == "return")
    {
        res = KW_return;
    }
    if (str == "cin")
    {
        res = KW_cin;
    }
    if (str == "cout")
    {
        res = KW_cout;
    }
    if (str == "tape")
    {
        res = KW_tape;
    }
    if (str == "jump")
    {
        res = KW_jump;
    }
    if (str == "if")
    {
        res = KW_if;
    }
    if (str == "then")
    {
        res = KW_then;
    }
    if (str == "pick")
    {
        res = KW_pick;
    }
    if (str == "create")
    {
        res = KW_create;
    }
    if (str == "set")
    {
        res = KW_set;
    }
    if (str == "func")
    {
        res = KW_func;
    }

    return res;

}