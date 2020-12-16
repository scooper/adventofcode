#include <Util/File.h>
#include <Util/String.h>
#include <string>
#include <vector>
#include <iostream>

#include "Ship.h"

int main()
{

    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day12/input.txt");
    //AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day12/inputTest.txt");

    Ship ship;
    Ship ship2;

    std::string line;
    while (file.NextLine(line))
    {
        ship.DoInstructionOld(line);
        ship2.DoInstructionNew(line);
    }

    std::cout << "Manhattan distance at end of journey (old): " << ship.GetManhattanDistance() << std::endl;
    std::cout << "Manhattan distance at end of journey (new): " << ship2.GetManhattanDistance() << std::endl;

    return 0;
}