#include <Util/File.h>
#include <string>
#include <iostream>

#include "Seat.h"

int main()
{
    AdventCommon::File fileLoader("D:/Projects/adventofcode/2020/inputs/Day5/input.txt");
    //AdventCommon::FileLoader fileLoader("D:/Projects/adventofcode/2020/inputs/Day5/inputTest.txt");

    Plane plane;

    int highestId = 0;

    std::string line;
    while (fileLoader.NextLine(line))
    {
        BoardingPass pass(line);
        //do something with input
        int seatId = pass.GetSeatID();

        //std::cout << seatId << std::endl;

        plane.OccupySeat(&pass);

        if (seatId > highestId)
            highestId = seatId;
    }

    std::vector<Seat> empty = plane.GetEmptySeats();

    for (Seat seat : empty)
    {
        // any empty seats that isnt on the front row or back row
        // bit annoying, but I found the min and max from the front and back with trial and error
        // could probably figure out what rows are empty in future, however (since it may not work for all inputs)
        if (seat.row > 6 && seat.row < 104)
        {
            std::cout << "Empty at id: " << seat.id << ", row: " << seat.row << ", col: " << seat.column << std::endl;
        }
    }

    std::cout << "Highest Seat ID: " << highestId << std::endl;

    return 0;
}