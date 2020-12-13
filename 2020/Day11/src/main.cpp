#include <iostream>
#include <string>
#include <vector>
#include <Util/File.h>
#include <Util/String.h>

#include "WaitingArea.h"

int main()
{
    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day11/input.txt");
    //AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day11/inputTest.txt");

    std::vector<std::string> input = AdventCommon::String::Split(file.AsStr(), "\n");

    // part 1
    WaitingArea wa(input);

    std::cout << "Num occupied when pattern doesn't change (old rules): " << wa.ApplyOldRules() << std::endl;

    // part 2
    WaitingArea wa2(input);

    std::cout << "Num occupied when pattern doesn't change (new rules): " << wa2.ApplyNewRules() << std::endl;

    return 0;
}