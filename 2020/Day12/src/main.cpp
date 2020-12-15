#include <Util/File.h>
#include <Util/String.h>
#include <string>
#include <vector>
#include <iostream>

#include "Ship.h"

int main()
{

    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day12/input.txt");

    Ship ship;

    std::string line;
    while (file.NextLine(line))
    {
        ship.DoInstruction(line);
    }

    std::cout << "Manhattan distance at end of journey: " << ship.GetManhattanDistance() << std::endl;

    return 0;
}