#include "RuntimeAnalyzer.h"
#include <iostream>
using namespace std;

RuntimeAnalyzer::RuntimeAnalyzer(char fileType)
{
    Reset();
    if (fileType == 'F')
    {
        fileName = "file.txt";
    }
    else if (fileType == 'K')
    {
        fileName = "kb.txt";
    }
    else
    {
        ErrorHandler("Unknown parameter value \"" + to_string(fileType) + "\" for fileType determination . character must be either K for keyboard or F for file.");
    }
}
void RuntimeAnalyzer::Reset()
{

    output = "";
}
std::string RuntimeAnalyzer::NameGenerator(NameType type)
{
    static int varCounter = 0;
    static int labelCounter = 0;
    string res = "";
    if (type == Variable)
    {
        res = "V" + to_string(varCounter);
        varCounter++;
        tempVariables.push_back(res);
    }
    else if (type == Label)
    {
        res = "L" + to_string(labelCounter);
        labelCounter++;
        tempLabels.push_back(res);
    }
    else
    {
        ErrorHandler("Unkown Name Type during name generation");
    }

    return res;
}

void RuntimeAnalyzer::ErrorHandler(string msg)
{
    cout << "Runtime Semantics Analyzer Error: " << msg << endl;
    exit(1);
}
void RuntimeAnalyzer::InitializeAsmVariables()
{
    for (int i = 0; i < tempVariables.size();i++)
    {
        output = output + tempVariables[i] + " 0\n";
    }
}
void RuntimeAnalyzer::ToAssembly()
{
    ofstream asmFile(fileName);
    if (asmFile.is_open())
    {
        asmFile << output;
        std::cout << "File created: " << fileName << std::endl;
        std::cout << "Output created: " << output << std::endl;
        asmFile.close();
    }
    else
    {
        ErrorHandler("Failed To create and open file " + fileName);
    }

}
void PrintTreeTest(TerminalNode* node, int level)
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
    PrintTreeTest(node->child1, level + 1);
    PrintTreeTest(node->child2, level + 1);
    PrintTreeTest(node->child3, level + 1);
    PrintTreeTest(node->child4, level + 1);
}
void RuntimeAnalyzer::SemanticsDriver(TerminalNode* curNode)
{

    if (curNode == nullptr)
    {

        return;
    }
    cout << "Currently Proccessing " + curNode->label + " node." << endl;
    if (curNode->label == PROGRAM_LABEL)
    {

        SemanticsDriver(curNode->child1);
        output = output + "BR toProgram\n";
        if (curNode->child2 != nullptr)
        {
            if (curNode->child2->label == FUNC_LABEL)
            {
                // SemanticsDriver(curNode->child2);
                output = output + "toProgram: NOOP\n";
                SemanticsDriver(curNode->child3);
            }
        }
        else
        {
            output = output + "toProgram: NOOP\n";
            SemanticsDriver(curNode->child3);
        }

        output = output + "STOP\n";
        InitializeAsmVariables();

    }
    else if (curNode->label == FUNC_LABEL)
    {

        string getFuncName = curNode->tk2.GetVal();
        functionName = getFuncName;
        funcPtr = curNode->child1;
        SemanticsDriver(curNode->child1);

    }
    else if (curNode->label == BLOCK_LABEL)
    {
        SemanticsDriver(curNode->child1);
        SemanticsDriver(curNode->child2);
    }
    else if (curNode->label == VARS_LABEL)
    {
        if (curNode->tk4.GetType() == Literal_Int)
        {
            output = output + "LOAD " + curNode->tk4.GetVal() + "\n";
        }
        else
        {
            output = output + "LOAD -7\n";
        }

        string newVarName = curNode->tk2.GetVal();

        output = output + "STORE " + newVarName + "\n";

        tempVariables.push_back(newVarName);

        if (curNode->tk5.GetVal() == ";")
        {
            SemanticsDriver(curNode->child1);
        }
    }
    else if (curNode->label == EXPR_LABEL)
    {
        if (curNode->tk1.GetType() == OP_Minus)
        {
            string leftVar = NameGenerator(Variable);
            output = output + "LOAD " + leftVar + "\n";
            SemanticsDriver(curNode->child1);
            output = output + "STORE " + leftVar + "\n";

            string rightVar = NameGenerator(Variable);
            output = output + "LOAD " + rightVar + "\n";
            SemanticsDriver(curNode->child2);
            output = output + "STORE " + rightVar + "\n";

            output = output + "LOAD " + leftVar + "\n";
            output = output + "SUB " + rightVar + "\n";
        }
        else
        {
            string exprVar = NameGenerator(Variable);
            output = output + "LOAD " + exprVar + "\n";
            SemanticsDriver(curNode->child1);
            output = output + "STORE " + exprVar + "\n";
        }
    }
    else if (curNode->label == N_LABEL)
    {
        if (curNode->tk1.GetType() == OP_Plus)
        {
            string leftVar = NameGenerator(Variable);
            output = output + "LOAD " + leftVar + "\n";
            SemanticsDriver(curNode->child1);
            output = output + "STORE " + leftVar + "\n";

            string rightVar = NameGenerator(Variable);
            output = output + "LOAD " + rightVar + "\n";
            SemanticsDriver(curNode->child2);
            output = output + "STORE " + rightVar + "\n";

            output = output + "LOAD " + leftVar + "\n";
            output = output + "ADD " + rightVar + "\n";
        }
        else if (curNode->tk1.GetType() == OP_ForwardSlash)
        {
            string leftVar = NameGenerator(Variable);
            output = output + "LOAD " + leftVar + "\n";
            SemanticsDriver(curNode->child1);
            output = output + "STORE " + leftVar + "\n";

            string rightVar = NameGenerator(Variable);
            output = output + "LOAD " + rightVar + "\n";
            SemanticsDriver(curNode->child2);
            output = output + "STORE " + rightVar + "\n";

            output = output + "LOAD " + leftVar + "\n";
            output = output + "DIV " + rightVar + "\n";
        }
        else {
            string exprVar = NameGenerator(Variable);
            output = output + "LOAD " + exprVar + "\n";
            SemanticsDriver(curNode->child1);
            output = output + "STORE " + exprVar + "\n";
        }
    }
    else if (curNode->label == A_LABEL)
    {
        if (curNode->tk1.GetType() == OP_Star)
        {
            string leftVar = NameGenerator(Variable);
            output = output + "LOAD " + leftVar + "\n";
            SemanticsDriver(curNode->child1);
            output = output + "STORE " + leftVar + "\n";

            string rightVar = NameGenerator(Variable);
            output = output + "LOAD " + rightVar + "\n";
            SemanticsDriver(curNode->child2);
            output = output + "STORE " + rightVar + "\n";

            output = output + "LOAD " + leftVar + "\n";
            output = output + "MULT " + rightVar + "\n";
        }
        else
        {
            string exprVar = NameGenerator(Variable);
            output = output + "LOAD " + exprVar + "\n";
            SemanticsDriver(curNode->child1);
            output = output + "STORE " + exprVar + "\n";
        }
    }
    else if (curNode->label == M_LABEL)
    {
        if (curNode->tk1.GetType() == OP_Carrot)
        {
            string exprVar = NameGenerator(Variable);
            output = output + "LOAD " + exprVar + "\n";

            SemanticsDriver(curNode->child1);

            string isZero = NameGenerator(Label);
            string isOne = NameGenerator(Label);
            string isNeg = NameGenerator(Label);
            string swap = NameGenerator(Label);
            string exit = NameGenerator(Label);


            output = output + "BRZERO " + isZero + "\n";
            output = output + "BRNEG " + isNeg + "\n";
            output = output + "SUB 1\n";
            output = output + "BRZERO " + isOne + "\n";
            output = output + "ADD 1\n";

            output = output + isNeg + ": NOOP\n";
            output = output + "ADD 1\n";
            output = output + "BRZERO " + isOne + "\n";
            output = output + "SUB 1\n";
            output = output + "BR " + swap + "\n";

            output = output + isZero + ": NOOP\n";
            output = output + "ADD 1\n";
            output = output + "BR " + exit + "\n";
            output = output + isOne + ": NOOP\n";
            output = output + swap + ": NOOP\n";
            output = output + "MULT -1\n";

            output = output + exit + ": NOOP\n";
            output = output + "STORE " + exprVar + "\n";
        }
        else
        {
            string exprVar = NameGenerator(Variable);
            output = output + "LOAD " + exprVar + "\n";
            SemanticsDriver(curNode->child1);
            output = output + "STORE " + exprVar + "\n";
        }
    }
    else if (curNode->label == R_LABEL)
    {
        if (curNode->tk1.GetType() == Identifier || curNode->tk1.GetType() == Literal_Int)
        {
            output = output + "LOAD " + curNode->tk1.GetVal() + "\n";
        }
        else
        {
            string exprVar = NameGenerator(Variable);
            output = output + "LOAD " + exprVar + "\n";
            SemanticsDriver(curNode->child1);
            output = output + "STORE " + exprVar + "\n";
        }
    }
    else if (curNode->label == STATS_LABEL)
    {
        SemanticsDriver(curNode->child1);
        SemanticsDriver(curNode->child2);
    }
    else if (curNode->label == MSTAT_LABEL)
    {
        SemanticsDriver(curNode->child1);
        SemanticsDriver(curNode->child2);
    }
    else if (curNode->label == STAT_LABEL)
    {
        SemanticsDriver(curNode->child1);
    }
    else if (curNode->label == IN_LABEL)
    {
        output = output + "READ " + curNode->tk2.GetVal() + "\n";
    }
    else if (curNode->label == OUT_LABEL)
    {
        string OutputVar = NameGenerator(Variable);
        output = output + "LOAD " + OutputVar + "\n";
        SemanticsDriver(curNode->child1);
        output = output + "STORE " + OutputVar + "\n";
        output = output + "WRITE " + OutputVar + "\n";
    }
    else if (curNode->label == IF_LABEL)
    {
        string LeftExprResultVar = NameGenerator(Variable);
        output = output + "LOAD " + LeftExprResultVar + "\n";
        SemanticsDriver(curNode->child1);
        output = output + "STORE " + LeftExprResultVar + "\n";
        EvenOddLeftExprValue = LeftExprResultVar;

        string RightExprResultVar = NameGenerator(Variable);
        output = output + "LOAD " + RightExprResultVar + "\n";
        SemanticsDriver(curNode->child3);
        output = output + "STORE " + RightExprResultVar + "\n";
        EvenOddRightExprValue = RightExprResultVar;

        if (curNode->child2->tk1.GetType() != Dot)
        {
            output = output + "SUB " + LeftExprResultVar + "\n";
        }
        string skipThenStatsLabel = NameGenerator(Label);

        SemanticsDriver(curNode->child2);

        SemanticsDriver(curNode->child4);

        output = output + skipThenStatsLabel + ": NOOP\n";
    }
    else if (curNode->label == PICK_LABEL)
    {
        string exprRes = NameGenerator(Variable);
        output = output + "LOAD " + exprRes + "\n";
        SemanticsDriver(curNode->child1);
        output = output + "STORE " + exprRes + "\n";
        output = output + "LOAD " + exprRes + "\n";

        string ifLabel = NameGenerator(Label);
        string elseLabel = NameGenerator(Label);
        string skipLabel = NameGenerator(Label);
        output = output + "BRPOS " + elseLabel + "\n";
        output = output + "BRNEG " + elseLabel + "\n";
        output = output + "BRZERO " + ifLabel + "\n";
        output = output + ifLabel + ": NOOP\n";
        SemanticsDriver(curNode->child2->child1);
        output = output + "BR " + elseLabel + "\n";
        output = output + elseLabel + ": NOOP\n";
        SemanticsDriver(curNode->child2->child2);
        output = output + skipLabel + ": NOOP\n";
    }
    else if (curNode->label == PICKBODY_LABEL)
    {
        //handled in PICK_LABEL
    }
    else if (curNode->label == LOOP1_LABEL)
    {

        string remainLoopLabel = NameGenerator(Label);

        output = output + remainLoopLabel + ": NOOP\n";

        string LeftExprResultVar = NameGenerator(Variable);
        output = output + "LOAD " + LeftExprResultVar + "\n";
        SemanticsDriver(curNode->child1);
        output = output + "STORE " + LeftExprResultVar + "\n";
        EvenOddLeftExprValue = LeftExprResultVar;

        string RightExprResultVar = NameGenerator(Variable);
        output = output + "LOAD " + RightExprResultVar + "\n";
        SemanticsDriver(curNode->child3);
        output = output + "STORE " + RightExprResultVar + "\n";
        EvenOddRightExprValue = RightExprResultVar;

        string exitLoopLabel = NameGenerator(Label);

        SemanticsDriver(curNode->child2);

        SemanticsDriver(curNode->child4);
        output = output + "BR " + remainLoopLabel + "\n";
        output = output + exitLoopLabel + ": NOOP\n";
    }
    else if (curNode->label == LOOP2_LABEL)
    {

        string remainLoopLabel = NameGenerator(Label);

        output = output + remainLoopLabel + ": NOOP\n";

        string LeftExprResultVar = NameGenerator(Variable);
        output = output + "LOAD " + LeftExprResultVar + "\n";
        SemanticsDriver(curNode->child2);
        output = output + "STORE " + LeftExprResultVar + "\n";
        EvenOddLeftExprValue = LeftExprResultVar;

        string RightExprResultVar = NameGenerator(Variable);
        output = output + "LOAD " + RightExprResultVar + "\n";
        SemanticsDriver(curNode->child4);
        output = output + "STORE " + RightExprResultVar + "\n";
        EvenOddRightExprValue = RightExprResultVar;

        string exitLoopLabel = NameGenerator(Label);

        SemanticsDriver(curNode->child1);

        SemanticsDriver(curNode->child3);

        output = output + "BR " + remainLoopLabel + "\n";
        output = output + exitLoopLabel + ": NOOP\n";
    }
    else if (curNode->label == ASSIGN_LABEL)
    {
        string reassignVar = curNode->tk2.GetVal();

        string exprRes = NameGenerator(Variable);
        output = output + "LOAD " + exprRes + "\n";
        SemanticsDriver(curNode->child1);
        output = output + "STORE " + exprRes + "\n";
        output = output + "LOAD " + reassignVar + "\n";
        output = output + "STORE " + exprRes + "\n";
    }
    else if (curNode->label == RO_LABEL)
    {
        if (tempLabels.empty()) {
            ErrorHandler("Failed To Generate Needed Branching Label");
        }

        string lastSkipLabel = tempLabels.back();
        if (curNode->tk1.GetType() == Dot)
        {
            string beginEvenOddCheck = NameGenerator(Label);

            string raiseOddFlag1 = NameGenerator(Label);
            string raiseEvenFlag1 = NameGenerator(Label);
            string raiseOddFlag2 = NameGenerator(Label);
            string raiseEvenFlag2 = NameGenerator(Label);

            string oddFlag1 = NameGenerator(Variable);
            string evenFlag1 = NameGenerator(Variable);
            string oddFlag2 = NameGenerator(Variable);
            string evenFlag2 = NameGenerator(Variable);

            string checkOtherNumber = NameGenerator(Label);
            string checkResults = NameGenerator(Label);
            output = output + "BR " + beginEvenOddCheck + "\n";

            output = output + raiseOddFlag1 + ": LOAD " + oddFlag1 + "\n";
            output = output + "ADD -1\n";
            output = output + "STORE " + oddFlag1 + "\n";
            output = output + "BR " + checkOtherNumber + "\n";

            output = output + raiseEvenFlag1 + ": LOAD " + evenFlag1 + "\n";
            output = output + "ADD 1\n";
            output = output + "STORE " + evenFlag1 + "\n";
            output = output + "BR " + checkOtherNumber + "\n";

            output = output + raiseOddFlag2 + ": LOAD " + oddFlag2 + "\n";
            output = output + "ADD -1\n";
            output = output + "STORE " + oddFlag2 + "\n";
            output = output + "BR " + checkResults + "\n";

            output = output + raiseEvenFlag2 + ": LOAD " + evenFlag2 + "\n";
            output = output + "ADD 1\n";
            output = output + "STORE " + evenFlag2 + "\n";
            output = output + "BR " + checkResults + "\n";

            string  copy1 = NameGenerator(Variable);
            string copy2 = NameGenerator(Variable);
            string makeCopy1Pos = NameGenerator(Label);
            string makeCopy2Pos = NameGenerator(Label);
            string madeCopy1Pos = NameGenerator(Label);
            string madeCopy2Pos = NameGenerator(Label);

            output = output + makeCopy1Pos + ": MULT -1\n";
            output = output + "STORE " + copy1 + "\n";
            output = output + "BR " + madeCopy1Pos + "\n";

            output = output + makeCopy2Pos + ": MULT -1\n";
            output = output + "STORE " + copy2 + "\n";
            output = output + "BR " + madeCopy2Pos + "\n";

            output = output + beginEvenOddCheck + ": LOAD " + EvenOddLeftExprValue + "\n";
            output = output + "STORE " + copy1 + "\n";
            output = output + "LOAD " + copy1 + "\n";


            string isCopy1Even = NameGenerator(Label);
            string isCopy2Even = NameGenerator(Label);


            output = output + "BRNEG " + makeCopy1Pos + " \n";
            output = output + madeCopy1Pos + ": NOOP" + "\n";
            output = output + isCopy1Even + ": NOOP" + "\n";
            output = output + "BRNEG " + raiseOddFlag1 + "\n";
            output = output + "BRZERO " + raiseEvenFlag1 + "\n";
            output = output + "SUB 2" + "\n";
            output = output + "BR " + isCopy1Even + "\n";

            output = output + checkOtherNumber + ": NOOP" + "\n";

            output = output + "LOAD " + EvenOddRightExprValue + "\n";
            output = output + "STORE " + copy2 + "\n";
            output = output + "LOAD " + copy2 + "\n";

            output = output + "BRNEG " + makeCopy2Pos + " \n";
            output = output + madeCopy2Pos + ": NOOP" + "\n";
            output = output + isCopy2Even + ": NOOP" + "\n";
            output = output + "BRNEG " + raiseOddFlag2 + "\n";
            output = output + "BRZERO " + raiseEvenFlag2 + "\n";
            output = output + "SUB 2" + "\n";
            output = output + "BR " + isCopy2Even + "\n";

            output = output + checkResults + ": NOOP" + "\n";

            string firstNumberEven = NameGenerator(Label);
            string firstNumberOdd = NameGenerator(Label);
            string secondNumberEven = NameGenerator(Label);
            string secondNumberOdd = NameGenerator(Label);


            output = output + "LOAD " + evenFlag1 + "\n";
            output = output + "BRPOS " + firstNumberEven + "\n";
            output = output + "LOAD " + oddFlag1 + "\n";
            output = output + "BRNEG " + firstNumberOdd + "\n";

            output = output + firstNumberOdd + ": LOAD " + oddFlag2 + "\n";
            output = output + "BRNEG " + secondNumberOdd + "\n";
            output = output + "BR " + lastSkipLabel + "\n";
            output = output + firstNumberEven + ": LOAD " + evenFlag2 + "\n";
            output = output + "BRNEG " + secondNumberEven + "\n";
            output = output + "BR " + lastSkipLabel + "\n";

            output = output + secondNumberEven + ": NOOP" + "\n";
            output = output + secondNumberOdd + ": NOOP" + "\n";


        }
        if (curNode->tk1.GetType() == OP_LessThan)
        { //x: 10, y: 20 x < y := y - x
            output = output + "BRNEG " + lastSkipLabel + "\n";
        }
        if (curNode->tk1.GetType() == OP_GreaterThan)
        {//x: 20, y: 10 x > y := y - x
            output = output + "BRPOS " + lastSkipLabel + "\n";

        }
        if (curNode->tk1.GetType() == OP_Equal)
        {

            output = output + "BRPOS " + lastSkipLabel + "\n";
            output = output + "BRNEG " + lastSkipLabel + "\n";
        }
        if (curNode->tk1.GetType() == OP_NotEqual)
        {
            output = output + "BRZERO " + lastSkipLabel + "\n";
        }
    }
    else if (curNode->label == LABEL_LABEL)
    {
        string newLabelName = curNode->tk2.GetVal();
        output = output + newLabelName + ": NOOP\n";
    }
    else if (curNode->label == GOTO_LABEL)
    {
        string labelName = curNode->tk2.GetVal();
        if (labelName == functionName)
        {
            SemanticsDriver(funcPtr);

        }
        else
        {
            output = output + "BR " + labelName + "\n";
        }
    }
    else
    {
        ErrorHandler("Unknown Node Label: " + curNode->label);
    }
}