#ifndef TOKEN_H
#define TOKEN_H
#include <string>
enum TokenType
{
    Eof, Identifier, Literal_Int,
    KW_start, KW_stop, KW_while, KW_repeat, KW_until,
    KW_label, KW_return, KW_cin, KW_cout, KW_tape, KW_jump, KW_if, KW_then,
    KW_pick, KW_create, KW_set, KW_func, OP_Assign, OP_LessThan, OP_GreaterThan, OP_Equal,
    OP_NotEqual, OP_Colon, OP_ColonEqual, OP_Plus, OP_Minus, OP_Star,
    OP_ForwardSlash, OP_Carrot, Dot, LeftPara, RightPara, Comma, LeftCurl,
    RightCurl, Semicolon, LeftBracket, RightBracket, Op_Or, OP_And

};
class Token
{
public:
    Token() {} //empty constructor
    Token(TokenType type, std::string value, int lineNumber, int charNumber);//token constructor with token type, string value, line num, char num params
    std::string ToString(); //converts token data to string 
    Token& operator=(const Token& other); //to assign token to token
    bool isEOF();//checks if token is a EOF token
    bool IsKeyword(std::string str); //checks if a string value is a keyword
    TokenType GetType();
    std::string GetVal();
private:
    std::string StringifyTokenType();//turns 'type', the TokenType enum to string
    TokenType KeywordStringToToken(std::string str); //takes keyword string and returns corresponding TokenType enum
    void IdentifierValidator(std::string str);//ensures Identifier doesnt violate length constraints
    TokenType type;//enum type of token
    std::string value; //string value of token
    int lineLocation;//line number of token
    int charLocation; //character number of token

};

#endif