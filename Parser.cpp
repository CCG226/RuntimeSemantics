#include "Parser.h"
using namespace std;
Parser::Parser(std::queue<Token> inputTokens)
{
    root = nullptr;
    ChangeInput(inputTokens);
}
void Parser::ChangeInput(std::queue<Token> inputTokens)
{
    programTokens = inputTokens;
}
void Parser::ErrorHandler(Token curTk, std::string terminal, std::string msg)
{
    cout << "Parser Error: " << "At Terminal " + terminal + ". " << endl;
    cout << "Message: " << msg << endl;
    cout << "Current Token Being Parsed: " << curTk.ToString() << endl;
}

TerminalNode* Parser::Driver()
{
    if (programTokens.front().GetType() == EOF)
    {
        ErrorHandler(programTokens.front(), "Driver", "Empty File");
    }
    root = ProgramTerminal();
    return root;
}
TerminalNode* Parser::GetProgramNode()
{
    return root;
}
TerminalNode* Parser::ProgramTerminal()
{
    TerminalNode* node = new TerminalNode("Program");
    node->child1 = VarsTerminal();
    Token tk = programTokens.front();
    if (tk.GetType() == KW_tape)
    {
        node->tk1 = tk;
        programTokens.pop();
        tk = programTokens.front();
        if (tk.GetType() == KW_func)
        {
            node->child2 = FuncTerminal();
        }

        node->child3 = BlockTerminal();
        return node;
    }
    ErrorHandler(tk, "Program", "Missing Keyword Token 'tape' ");
    exit(1);
}
TerminalNode* Parser::FuncTerminal()
{
    TerminalNode* node = new TerminalNode("Func");
    Token tk = programTokens.front();

    if (tk.GetType() == KW_func)
    {
        node->tk1 = tk;
        programTokens.pop();
        tk = programTokens.front();
        if (tk.GetType() == Identifier)
        {
            node->tk2 = tk;
            programTokens.pop();
            node->child1 = BlockTerminal();
            return node;
        }
        ErrorHandler(tk, "Func", "Missing Identifier Token");
    }
    ErrorHandler(tk, "Func", "Missing Keyword Token 'func' ");
    exit(1);
}
TerminalNode* Parser::BlockTerminal()
{
    TerminalNode* node = new TerminalNode("Block");
    Token tk = programTokens.front();

    if (tk.GetType() == LeftCurl)
    {
        node->tk1 = tk;
        programTokens.pop();
        node->child1 = VarsTerminal();
        node->child2 = StatsTerminal();
    }
    else {
        ErrorHandler(tk, "Block", "Missing block starting Token '{' ");
    }
    tk = programTokens.front();

    if (tk.GetType() == RightCurl)
    {
        node->tk2 = tk;
        programTokens.pop();
        return node;
    }
    else {
        ErrorHandler(tk, "Block", "Missing block ending Token '}' ");
    }
    exit(1);
}
TerminalNode* Parser::VarsTerminal()
{
    TerminalNode* node = new TerminalNode("Vars");
    Token tk = programTokens.front();

    if (tk.GetType() == KW_create)
    {
        node->tk1 = tk;
        programTokens.pop();

        tk = programTokens.front();


        if (tk.GetType() == Identifier)
        {
            node->tk2 = tk;
            programTokens.pop();
            tk = programTokens.front();


            if (tk.GetType() == Semicolon)
            {
                node->tk3 = tk;
                programTokens.pop();
                return node;
            }
            else if (tk.GetType() == OP_ColonEqual)
            {
                node->tk3 = tk;
                programTokens.pop();
                tk = programTokens.front();

                if (tk.GetType() == Literal_Int)
                {
                    node->tk4 = tk;
                    programTokens.pop();
                    tk = programTokens.front();
                    if (tk.GetType() == Semicolon)
                    {
                        node->tk5 = tk;
                        programTokens.pop();
                        node->child1 = VarsTerminal();
                        return node;
                    }
                }


            }
            ErrorHandler(tk, "Vars", "Failed to create variable(s). Missing ';' or ':=' ");
        }
        ErrorHandler(tk, "Vars", "Failed to create variable(s). Missing Identifier ");
    }
    else {
        return nullptr;
    }
    exit(1);
}
TerminalNode* Parser::ExprTerminal()
{
    TerminalNode* node = new TerminalNode("Expr");
    node->child1 = NTerminal();

    Token tk = programTokens.front();

    if (tk.GetType() == OP_Minus)
    {
        node->tk1 = tk;
        programTokens.pop();

        node->child2 = ExprTerminal();
    }

    return node;
}
TerminalNode* Parser::NTerminal()
{
    TerminalNode* node = new TerminalNode("N");
    Token tk = programTokens.front();

    if (tk.GetType() == OP_ForwardSlash)
    {
        node->tk1 = tk;
        programTokens.pop();
        node->child1 = ATerminal();
        return node;
    }
    else if (tk.GetType() == OP_Plus)
    {
        node->tk1 = tk;
        programTokens.pop();
        node->child1 = ATerminal();
        return node;
    }
    else {
        node->child1 = ATerminal();
        return node;
    }

}
TerminalNode* Parser::ATerminal()
{
    TerminalNode* node = new TerminalNode("A");
    node->child1 = MTerminal();
    Token tk = programTokens.front();

    if (tk.GetType() == OP_Star)
    {
        node->tk1 = tk;
        programTokens.pop();
        node->child2 = ATerminal();
        return node;
    }
    return node;

}
TerminalNode* Parser::MTerminal()
{
    TerminalNode* node = new TerminalNode("A");
    Token tk = programTokens.front();

    if (tk.GetType() == OP_Carrot)
    {
        node->tk1 = tk;
        programTokens.pop();
        node->child1 = MTerminal();
        return node;
    }
    else {
        node->child1 = RTerminal();
        return node;
    }
}
TerminalNode* Parser::RTerminal()
{
    TerminalNode* node = new TerminalNode("R");
    Token tk = programTokens.front();


    if (tk.GetType() == LeftPara)
    {
        node->tk1 = tk;
        node->child1 = ExprTerminal();
        tk = programTokens.front();
        if (tk.GetType() == RightPara)
        {
            node->tk2 = tk;
            programTokens.pop();
            return node;
        }
        else
        {
            ErrorHandler(tk, "R", "Failed to build (expr). Missing ending ')' ");
        }
    }
    else if (tk.GetType() == Identifier)
    {
        node->tk1 = tk;
        programTokens.pop();
        return node;
    }
    else if (tk.GetType() == Literal_Int)
    {
        node->tk1 = tk;
        programTokens.pop();
        return node;
    }
    else
    {
        ErrorHandler(tk, "R", "Invalid construction of R non terminal. Missing starting '(' for (expr) or Identifier or Integer ");
    }
    exit(1);
}
TerminalNode* Parser::StatsTerminal()
{
    TerminalNode* node = new TerminalNode("Stats");
    node->child1 = StatTerminal();

    node->child2 = MstatTerminal();

    return node;
}
TerminalNode* Parser::MstatTerminal()
{
    cout << "HI" << endl;
    TerminalNode* node = new TerminalNode("Mstat");
    Token tk = programTokens.front();
    if (tk.GetType() != Identifier && tk.GetType() != LeftCurl && tk.GetType() != KW_cout && tk.GetType() != KW_if && tk.GetType() != KW_pick && tk.GetType() != KW_while && tk.GetType() != KW_repeat && tk.GetType() != KW_cin && tk.GetType() != KW_set && tk.GetType() != KW_label && tk.GetType() != KW_jump)
    {
        cout << "BRUH";
        return nullptr;
    }
    node->child1 = StatTerminal();

    node->child2 = MstatTerminal();

    return node;
}
TerminalNode* Parser::StatTerminal()
{
    TerminalNode* node = new TerminalNode("Stat");
    Token tk = programTokens.front();

    if (tk.GetType() == KW_cin)
    {
        node->child1 = InTerminal();

    }
    else if (tk.GetType() == KW_cout)
    {
        cout << "2BRUH";
        node->child1 = OutTerminal();

    }
    else if (tk.GetType() == LeftCurl)
    {
        node->child1 = BlockTerminal();
        return node;
    }
    else if (tk.GetType() == KW_if)
    {
        node->child1 = IfTerminal();

    }
    else if (tk.GetType() == KW_while)
    {
        node->child1 = Loop1Terminal();

    }
    else if (tk.GetType() == KW_repeat)
    {
        node->child1 = Loop2Terminal();

    }
    else if (tk.GetType() == KW_set || tk.GetType() == Identifier)
    {
        node->child1 = AssignTerminal();

    }
    else if (tk.GetType() == KW_jump)
    {
        node->child1 = GotoTerminal();

    }
    else if (tk.GetType() == KW_label)
    {
        node->child1 = LabelTerminal();

    }
    else if (tk.GetType() == KW_pick)
    {
        node->child1 = PickTerminal();

    }
    else {
        ErrorHandler(tk, "stat", "Illegal stat non terminal. A stat must lead to in, out, block, if, loop1, loop2, assign, goto, label, or pick terminal. But current token makes it impossible.");
    }
    tk = programTokens.front();

    if (tk.GetType() == Semicolon)
    {
        node->tk1 = tk;
        programTokens.pop();
        return node;
    }
    else {
        ErrorHandler(tk, "stat", "Missing ';' at end of statement");
    }
    exit(1);
}
TerminalNode* Parser::InTerminal()
{
    TerminalNode* node = new TerminalNode("In");
    Token tk = programTokens.front();

    if (tk.GetType() == KW_cin)
    {
        node->tk1 = tk;
        programTokens.pop();
        tk = programTokens.front();
        if (tk.GetType() == Identifier)
        {
            node->tk2 = tk;
            programTokens.pop();
            return node;
        }
        else
        {
            ErrorHandler(tk, "in", "Missing identifier after cin keyword");
        }
    }
    else {
        ErrorHandler(tk, "in", "Requires cin keyword");
    }
    exit(1);
}
TerminalNode* Parser::OutTerminal()
{
    TerminalNode* node = new TerminalNode("Out");
    Token tk = programTokens.front();

    if (tk.GetType() == KW_cout)
    {
        node->tk1 = tk;
        programTokens.pop();
        node->child1 = ExprTerminal();

        return node;
    }
    else {
        ErrorHandler(tk, "out", "Requires cout keyword");
    }
    exit(1);
}
TerminalNode* Parser::IfTerminal()
{
    TerminalNode* node = new TerminalNode("If");
    Token tk = programTokens.front();

    if (tk.GetType() == KW_if)
    {
        node->tk1 = tk;
        programTokens.pop();
        tk = programTokens.front();
        if (tk.GetType() == LeftBracket)
        {
            node->tk2 = tk;
            programTokens.pop();
            node->child1 = ExprTerminal();
            node->child2 = ROTerminal();
            node->child3 = ExprTerminal();
        }
        else {
            ErrorHandler(tk, "if", "Missing Required '[' to contain if expression");
        }
        tk = programTokens.front();
        if (tk.GetType() == RightBracket)
        {
            node->tk3 = tk;
            programTokens.pop();
            tk = programTokens.front();
            if (tk.GetType() == KW_then)
            {
                node->tk4 = tk;
                programTokens.pop();
                node->child4 = StatTerminal();
                return node;
            }
            else {
                ErrorHandler(tk, "if", "Missing Required then keyword to execute statements if if statement is true ");
            }
        }
        else {
            ErrorHandler(tk, "if", "Missing Required ']' to contain if expression");
        }
    }
    exit(1);
}
TerminalNode* Parser::PickTerminal()
{
    TerminalNode* node = new TerminalNode("Pick");
    Token tk = programTokens.front();
    if (tk.GetType() == KW_pick)
    {
        node->tk1 = tk;
        programTokens.pop();
        node->child1 = ExprTerminal();
        node->child2 = PickbodyTerminal();
        return node;
    }
    else
    {
        ErrorHandler(tk, "pick", "Missing Required pick keyword to create pick conditionals ");
    }
    exit(1);
}
TerminalNode* Parser::PickbodyTerminal()
{
    TerminalNode* node = new TerminalNode("Pickbody");
    node->child1 = StatTerminal();
    Token tk = programTokens.front();
    if (tk.GetType() == OP_Colon)
    {
        node->tk1 = tk;
        programTokens.pop();
        node->child2 = StatTerminal();
        return node;
    }
    else
    {
        ErrorHandler(tk, "pickbody", "Missing Required ':' to seperate statements");
    }
    exit(1);
}
TerminalNode* Parser::Loop1Terminal()
{
    TerminalNode* node = new TerminalNode("Loop1");
    Token tk = programTokens.front();
    if (tk.GetType() == KW_while)
    {
        node->tk1 = tk;
        programTokens.pop();

        tk = programTokens.front();
        if (tk.GetType() == LeftBracket)
        {
            node->tk2 = tk;
            programTokens.pop();
            node->child1 = ExprTerminal();
            node->child2 = ROTerminal();
            node->child3 = ExprTerminal();

            tk = programTokens.front();
            if (tk.GetType() == RightBracket)
            {
                node->tk3 = tk;
                programTokens.pop();
                node->child4 = StatTerminal();
                return node;
            }
            else {
                ErrorHandler(tk, "loop1", "Missing Required ']' to end while loop expression");
            }
        }
        else {
            ErrorHandler(tk, "loop1", "Missing Required '[' to start while loop expression");
        }
    }
    else {
        ErrorHandler(tk, "loop1", "Missing Required while keyword to create while loop");
    }
    exit(1);
}
TerminalNode* Parser::Loop2Terminal()
{
    TerminalNode* node = new TerminalNode("Loop2");
    Token tk = programTokens.front();
    if (tk.GetType() == KW_repeat)
    {
        node->tk1 = tk;
        programTokens.pop();
        node->child1 = StatTerminal();
        tk = programTokens.front();
        if (tk.GetType() == KW_until)
        {
            node->tk2 = tk;
            programTokens.pop();
            tk = programTokens.front();
            if (tk.GetType() == LeftBracket)
            {
                node->tk3 = tk;
                programTokens.pop();
                node->child2 = ExprTerminal();
                node->child3 = ROTerminal();
                node->child4 = ExprTerminal();
                tk = programTokens.front();
                if (tk.GetType() == RightBracket)
                {
                    node->tk4 = tk;
                    programTokens.pop();
                    return node;
                }
                else {
                    ErrorHandler(tk, "loop1", "Missing Required ']' to start repeat loop expression");
                }
            }
            else {
                ErrorHandler(tk, "loop1", "Missing Required '[' to start repeat loop expression");
            }
        }
        else {
            ErrorHandler(tk, "loop2", "Missing Required until keyword to do repeat loop expression");
        }
    }
    else {
        ErrorHandler(tk, "loop2", "Missing Required repeat keyword to create while loop");
    }
    exit(1);
}
TerminalNode* Parser::AssignTerminal()
{
    TerminalNode* node = new TerminalNode("Assign");
    Token tk = programTokens.front();
    if (tk.GetType() == KW_set)
    {
        node->tk1 = tk;
        programTokens.pop();
        Token tk = programTokens.front();
        if (tk.GetType() == Identifier)
        {
            node->tk2 = tk;
            programTokens.pop();

            Token tk = programTokens.front();
            if (tk.GetType() == OP_Assign)
            {
                node->tk3 = tk;
                programTokens.pop();
                node->child1 = ExprTerminal();
                return node;
            }
            else {
                ErrorHandler(tk, "assign", "Missing Required '=' operator in assignment");
            }
        }
        else {
            ErrorHandler(tk, "assign", "Missing Required Identifier to set");
        }
    }
    else if (tk.GetType() == Identifier)
    {
        node->tk1 = tk;
        programTokens.pop();
        Token tk = programTokens.front();
        if (tk.GetType() == OP_Assign)
        {
            node->tk2 = tk;
            programTokens.pop();
            node->child1 = ExprTerminal();
            return node;
        }
        else {
            ErrorHandler(tk, "assign", "Missing Required '=' operator in assignment");
        }
    }
    else
    {
        if (tk.GetType() == Identifier)
        {
            ErrorHandler(tk, "assign", "Missing Required Identifier to set");
        }
        if (tk.GetType() == KW_set)
        {
            ErrorHandler(tk, "assign", "Missing Required set keyword");
        }
    }
    exit(1);
}
TerminalNode* Parser::ROTerminal()
{
    TerminalNode* node = new TerminalNode("RO");
    Token tk = programTokens.front();
    if (tk.GetType() == OP_LessThan)
    {
        node->tk1 = tk;
        programTokens.pop();
        return node;
    }
    else if (tk.GetType() == OP_GreaterThan)
    {
        node->tk1 = tk;
        programTokens.pop();
        return node;
    }
    else if (tk.GetType() == OP_Equal)
    {
        node->tk1 = tk;
        programTokens.pop();
        return node;
    }
    else if (tk.GetType() == Dot)
    {
        node->tk1 = tk;
        programTokens.pop();
        tk = programTokens.front();
        if (tk.GetType() == Dot)
        {
            node->tk2 = tk;
            programTokens.pop();
            tk = programTokens.front();
            if (tk.GetType() == Dot)
            {
                node->tk3 = tk;
                programTokens.pop();
                return node;
            }
            else {
                ErrorHandler(tk, "RO", "Missing last . in ...");
            }
        }
        else {
            ErrorHandler(tk, "RO", "Missing second . in ...");
        }

    }
    else if (tk.GetType() == OP_NotEqual)
    {
        node->tk1 = tk;
        programTokens.pop();
        return node;
    }
    else
    {
        ErrorHandler(tk, "RO", "Missing starting '<', '>', '==',first '.' in ..., '=!=' in RO");
    }
    exit(1);
}
TerminalNode* Parser::LabelTerminal()
{
    TerminalNode* node = new TerminalNode("Label");
    Token tk = programTokens.front();
    if (tk.GetType() == KW_label)
    {
        node->tk1 = tk;
        programTokens.pop();
        tk = programTokens.front();
        if (tk.GetType() == Identifier)
        {
            node->tk2 = tk;
            programTokens.pop();
            return node;
        }
        else {
            ErrorHandler(tk, "label", "Missing Identifier after label");
        }
    }
    else {
        ErrorHandler(tk, "label", "Missing keyword 'label'");
    }
    exit(1);
}
TerminalNode* Parser::GotoTerminal()
{
    TerminalNode* node = new TerminalNode("Goto");
    Token tk = programTokens.front();
    if (tk.GetType() == KW_jump)
    {
        node->tk1 = tk;
        programTokens.pop();
        tk = programTokens.front();
        if (tk.GetType() == Identifier)
        {
            node->tk2 = tk;
            programTokens.pop();
            return node;
        }
        else {
            ErrorHandler(tk, "goto", "Missing Identifier after jump");
        }
    }
    else {
        ErrorHandler(tk, "goto", "Missing keyword 'jump'");
    }
    exit(1);
}
void Parser::PrintTree(TerminalNode* node, int level)
{
    if (node == nullptr)
    {
        return;
    }
    for (int i = 0; i < level; i++)
    {
        std::cout << "\t";
    }

    std::cout << "Label: " << node->label << " Tokens: (";

    std::cout << node->tk1.GetVal() << " ";
    std::cout << node->tk2.GetVal() << " ";
    std::cout << node->tk3.GetVal() << " ";
    std::cout << node->tk4.GetVal() << " ";
    std::cout << node->tk5.GetVal() << ")" << std::endl;
    PrintTree(node->child1, level + 1);
    PrintTree(node->child2, level + 1);
    PrintTree(node->child3, level + 1);
    PrintTree(node->child4, level + 1);
}
void Parser::Clear()
{
    DeleteNode(this->root);
    this->root = nullptr;
}
void Parser::DeleteNode(TerminalNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    DeleteNode(node->child1);
    DeleteNode(node->child2);
    DeleteNode(node->child3);
    DeleteNode(node->child4);
    delete node;
}