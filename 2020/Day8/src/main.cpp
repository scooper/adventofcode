#include <Util/File.h>
#include <Util/String.h>
#include <string>
#include <vector>
#include <iostream>

#include "Program.h"

int main()
{
    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day8/input.txt");
    //AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day8/inputTest.txt");

    std::vector<std::string> input = AdventCommon::String::Split(file.AsStr(), "\n");
    
    Program program(input);

    for (std::string instruction : input)
    {
        std::cout << instruction << std::endl;
    }

    program.Execute();
    int last = program.Reset();

    program.Execute();

    return 0;
}