#include <iostream>
#include <vector>
#include <Util/File.h>
#include <string>
#include <algorithm>

int main()
{

    //AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day10/input.txt");
    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day10/inputTest.txt");
    //AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day10/inputTest2.txt");

    std::vector<int> adapters;

    std::string line;

    while (file.NextLine(line))
    {
        adapters.push_back(atoi(line.c_str()));
    }

    int startingAdapter = 0;
    int maxAdapter = *std::max_element(adapters.begin(), adapters.end());
    // end adapter = our device adapter which is always 3 larger than largest jolt adapter
    int endAdapter = maxAdapter + 3;

    adapters.insert(adapters.begin(), startingAdapter);
    adapters.push_back(endAdapter);

    // the possible differences (maybe should be a map of int, int for diff number and count since it's more scalable)
    int diff1 = 0, diff2 = 0, diff3 = 0;

    std::sort(adapters.begin(), adapters.end(), [](const int& a, const int& b) { return a < b; });

    for (std::vector<int>::const_iterator it = adapters.begin() + 1; it != adapters.end(); it++)
    {
        int diff = *it - *(it - 1);

        if (diff == 1)
            diff1++;
        else if (diff == 2)
            diff2++;
        else if (diff == 3)
            diff3++;
        else
            std::cout << "Diff is not 1, 2 or 3 so something is wrong" << std::endl;

    }

    // output
    std::cout << "1 Jolt Differences: " << diff1 << std::endl;
    std::cout << "2 Jolt Differences: " << diff2 << std::endl;
    std::cout << "3 Jolt Differences: " << diff3 << std::endl;

    std::cout << "1JD x 3JD = " << diff1 * diff3 << std::endl;

    // sort top to bottom
    std::sort(adapters.begin(), adapters.end(), [](const int& a, const int& b) { return a > b; });

    int validTotal = 1;

    for (std::vector<int>::const_iterator it = adapters.begin(); it != adapters.end()-1; it++)
    {
        int validOptions = 0;
        for (std::vector<int>::const_iterator it2 = it + 1; it2 != adapters.end(); it2++)
        {

            int targetJoltage = *it;
            int testJoltage = *it2;

            // get joltage difference
            if ((targetJoltage - testJoltage) > 3)
            {
                break;
            }
            else
            {
                validOptions++;
            }
        }

        validTotal *= validOptions;
    }


    std::cout << "Total Valid Adapter Configurations: " << validTotal << std::endl;


    return 0;
}

// TODO: write recursive function that traverses tree of possible options in a depth-first-search manner
//       look at notes taken to refresh memory of how to approach the problem
