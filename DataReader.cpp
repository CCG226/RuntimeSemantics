#include "DataReader.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
// by default DataReader has no file access, reads key input, and splits input strings into vectors via whitespace ' '
DataReader::DataReader()
{
    inputType = Keyboard;
    splitChar = ' ';
    fileName = "";
}
// setter for input file name
void DataReader::UpdateDataFile(std::string fileName)
{
    this->fileName = fileName;

    if (!FileExists())
    {
        cout << "File Does Not Exist!" << endl;
        exit(1);
    }
}
// setter for vector spliter character
void DataReader::ChangeVectorSpliter(char newSpliter)
{
    splitChar = newSpliter;
}
// swaps DataReader to keyboard input mode
void DataReader::KeyboardMode()
{
    inputType = Keyboard;
}
// swaps DataReader to file input mode
void DataReader::FileMode()
{
    inputType = File;
}
char DataReader::CurrentMode()
{
    if (inputType == File)
    {
        return 'F';
    }
    else if (inputType == Keyboard)
    {
        return 'K';
    }
    else
    {
        cout << "Unknown Input Type." << endl;
        exit(1);
    }
}
// if file exists then return true else return false
bool DataReader::FileExists()
{
    std::ifstream file(fileName);

    bool exists = file.good();

    file.close();

    return exists;
}
//// reads input data into string, methodology depends on inputType enum variable
string DataReader::ToString()
{
    string results;

    switch (inputType)
    {
    case Keyboard:
        results = KeyboardToString();
        break;
    case File:
        results = FileToString();
        break;
    default:
        cout << "Invalid Input Type." << endl;
        exit(1);
    }
    return results;
}
// reads data from console using getline and stores data in a string vector
string DataReader::KeyboardToString()
{
    string input;
    string line;
    while (getline(cin, line))
    {
        input += line;
    }
    return input;
}
// reads data from file character by character and stores data in string
string DataReader::FileToString()
{
    ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        cout << "Failed To Open Argument File " << fileName << endl;
        exit(1);
    }
    stringstream buffer;

    buffer << inputFile.rdbuf();

    inputFile.close();

    return buffer.str();
}
// reads input data into vector of string, methodology depends on inputType enum variable
vector<string> DataReader::ToVector()
{
    vector<string> results;

    switch (inputType)
    {
    case Keyboard:
        results = KeyboardToVector();
        break;
    case File:
        results = FileToVector();
        break;
    default:
        cout << "Invalid Input Type." << endl;
        exit(1);
    }

    dataVector.clear();

    return results;
}
// reads data from file character by character and stores data in string vector
vector<string> DataReader::FileToVector()
{

    string wordBuilder = "";
    char nextChar = ' ';

    ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        cout << "Failed To Open Argument File " << fileName << endl;
        exit(1);
    }

    while (inputFile.get(nextChar))
    {
        if (nextChar == splitChar)
        {
            VectorAdder(wordBuilder);
            wordBuilder = "";
        }
        else
        {
            wordBuilder = wordBuilder + nextChar;
        }
    }

    inputFile.close();

    VectorAdder(wordBuilder);

    return dataVector;
}
// reads data from console using getline and stores data in a string vector
vector<string> DataReader::KeyboardToVector()
{
    string input = KeyboardToString();

    string wordBuilder = "";
    for (int i = 0; static_cast<size_t>(i) < input.length(); i++)
    {
        if (input[i] == splitChar)
        {
            VectorAdder(wordBuilder);
            wordBuilder = "";
        }
        else
        {
            wordBuilder = wordBuilder + input[i];
        }
    }

    VectorAdder(wordBuilder);

    return dataVector;
}

// adds new token to vector string if token is NOT empty
void DataReader::VectorAdder(string word)
{
    if (word != "")
    {
        dataVector.push_back(word);
    }

    return;
}