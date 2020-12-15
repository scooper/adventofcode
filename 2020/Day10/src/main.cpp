#include <iostream>
#include <vector>
#include <Util/File.h>
#include <string>
#include <algorithm>
#include <unordered_map>

uint64_t DepthFirstRecursiveSearch(std::vector<int>::const_iterator start, std::vector<int>::const_iterator end);

int main()
{

    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day10/input.txt");
    //AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day10/inputTest.txt");
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

    std::cout << "Total Valid Adapter Configurations: " << DepthFirstRecursiveSearch(adapters.begin(), adapters.end()) << std::endl;

    return 0;
}


std::unordered_map<int, uint64_t> cache;

//
// This is fucked: works for input examples 1 and 2 but not the big input
// something is wrong with this function, maybe too slow or some condition I'm missing where it goes into an infinite recursion
// this can probably be done with some simple counting maths
//
// EDIT: it was too slow, used a cache instead, fuck being clever
//
uint64_t DepthFirstRecursiveSearch(std::vector<int>::const_iterator start, std::vector<int>::const_iterator end)
{
    if (start == end-1)
        return 1;
    
    // skip the nightmare
    if (cache.find(*start) != cache.end())
        return cache[*start];      

    uint64_t numOptions = 0;

    for (std::vector<int>::const_iterator it = start+1; it != end; it++)
    {
        int targetJoltage = *start;
        int testJoltage = *it;

        int diff = testJoltage - targetJoltage;

        if (diff <= 3)
            numOptions += DepthFirstRecursiveSearch(it, end);
        else
            break;     
    }

    // add to cache so we never have to calculate it again
    cache[*start] = numOptions;

    return numOptions;
}
