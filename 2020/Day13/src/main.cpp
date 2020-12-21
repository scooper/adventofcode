#include <Util/File.h>
#include <Util/String.h>
#include <iostream>
#include <string>
#include <vector>

struct BusTime
{
    int time;
    int busId;
    int waitTime;
};

struct BusListing
{
    int id;
    bool unrestricted;
};

void Part1(std::vector<int>& busIDs, int& earliestDepartTime)
{
    BusTime earlistBusTime = { 0,0,0 };

    for (int i = earliestDepartTime; i > 0; i++)
    {
        for (int busID : busIDs)
        {
            if (i % busID == 0)
            {
                earlistBusTime.time = i;
                earlistBusTime.busId = busID;
                earlistBusTime.waitTime = i - earliestDepartTime;
                i = -1;
                break;
            }
        }
    }

    std::cout << "Bus ID (" << earlistBusTime.busId << ") at time " << earlistBusTime.time << " with wait time "
        << earlistBusTime.waitTime << " gives " << earlistBusTime.waitTime * earlistBusTime.busId << std::endl;
    
    return;
}

// WARNING: SLOW and just all around awful
void Part2(std::vector<BusListing> listings, uint64_t minhint = 0)
{
    bool outerLoopBreak = false;
    uint64_t i = minhint;
    while(!outerLoopBreak)
    {
        for (uint64_t j = 0; j < listings.size(); j++)
        {
            uint64_t minute = j + i;
            if (listings[j].unrestricted)
                continue;
            if (minute % listings[j].id != 0)
            {
                break;
            }

            if (j == listings.size() - 1)
            {
                std::cout << "Earliest minute fulfilling conditions is " << i << std::endl;
                outerLoopBreak = true;
                break;
            }

            // if complete, outer loop -1 and break while adding the earliest time stamp info (i)
        }
        i++;
    }

    return;
}

int main()
{
    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day13/input.txt");
    //AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day13/inputTest.txt");

    std::string line;
    file.NextLine(line);

    int earliestDepartTime = atoi(line.c_str());
    
    file.NextLine(line);

    std::vector<std::string> busIDStrings = AdventCommon::String::Split(line, ",");

    std::vector<int> busIDs;
    std::vector<BusListing> busListings;

    for (std::string id : busIDStrings)
    {
        if (AdventCommon::String::IsNumber(id))
        {
            int idNum = atoi(id.c_str());
            busIDs.push_back(idNum);
            busListings.push_back({ idNum, false });
        }
        else
        {
            busListings.push_back({ -1,true });
        }
    }

    Part1(busIDs, earliestDepartTime);
    Part2(busListings, 100000000000000);

    return 0;
}