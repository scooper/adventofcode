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


    for (std::string id : busIDStrings)
    {
        if (AdventCommon::String::IsNumber(id))
        {
            busIDs.push_back(atoi(id.c_str()));
        }
    }

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

    return 0;
}