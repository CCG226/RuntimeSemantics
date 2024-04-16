
#ifndef DATAREADER_H
#define DATAREADER_H
#include <string>
#include <vector>
// represents the mode are DataReader is in so it knows where to read data from
enum Mode
{
    Keyboard,
    File
};
class DataReader
{

public:
    DataReader();                              // constructor
    void UpdateDataFile(std::string fileName); // changes file DataReader reads from
    void ChangeVectorSpliter(char newSpliter); // this method can change splitChar to another character
    void KeyboardMode();                       // DataReader reads keyboard input from console
    void FileMode();                           // DataReader reads input from text file
    char CurrentMode();
    std::vector<std::string> ToVector();       // reads input to vector of strings
    std::string ToString();                     //reads input to string

private:
    char splitChar;                      // for ToVector() method, this character is used to split input string into vector strings by character stored in this variable
    std::string fileName;                // file name DataReader reads from
    std::vector<std::string> dataVector; // resulting data created from ToVector
    Mode inputType;                      // inputType determines where DataReader reads data from

    bool FileExists(); // checks if file exists
    std::string FileToString(); // converts data from file to string
    std::string KeyboardToString();// converts console input from file to string
    std::vector<std::string> FileToVector();     // converts data from file into vector of strings
    std::vector<std::string> KeyboardToVector(); // converts console input to vector of strings
    void VectorAdder(std::string token);         // adds a new string to dataVector
};
#endif