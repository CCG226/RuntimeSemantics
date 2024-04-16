#include <iostream>
#include <cstring>
#include "DataReader.h"
#include "Scanner.h"
#include "Parser.h"
#include "StaticAnalyzer.h"
#include "RuntimeAnalyzer.h"
using namespace std;

bool WasFileGiven(int argc, char* argv[]); // checks if 1 argument was given for filename
// testing environment
int main(int argc, char* argv[])
{
  cout << endl;
  DataReader reader;

  if (WasFileGiven(argc, argv))
  {
    reader.FileMode();
    reader.UpdateDataFile(argv[1]);
  }

  Scanner scanner(reader.ToString());

  Parser parser(scanner.Driver());

  StaticAnalyzer statAnalyzer(parser.Driver());

  statAnalyzer.SemanticsDriver();

  RuntimeAnalyzer finalAnalyzer(reader.CurrentMode());

  finalAnalyzer.SemanticsDriver();

  parser.Clear();

  return 0;
}
// if argument count is 2 and second element in argv is not empty,
// if so we have a file name we can access
bool WasFileGiven(int argc, char* argv[])
{
  const int ARGUMENT_COUNT = 2;

  const int EMPTY_INPUT = 0;

  if (argc != ARGUMENT_COUNT)
  {
    return false;
  }
  if (argv[1] == nullptr || strlen(argv[1]) == EMPTY_INPUT)
  {
    cout << "Error: Input Argument Cannot Be Empty!" << endl;
    exit(1);
  }

  return true;
}