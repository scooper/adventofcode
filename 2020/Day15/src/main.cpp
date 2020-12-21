#include <Util/File.h>
#include <Util/String.h>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

// TODO: possibly a sequences challenge (solve mathematically?)

// ... I know, globals bad...

std::vector<int> nums;
// holds the numbers that have been spoken, and the index when they were last spoken
std::unordered_map<int, int> numberMap;

int GetNumSpokenAtN(int N);

int main()
{
    //AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day15/input.txt");
    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day15/inputTest.txt");

    for (std::string num : AdventCommon::String::Split(file.AsStr(), ","))
    {
        nums.push_back(atoi(num.c_str()));
    }

    int numspokenat2020 = GetNumSpokenAtN(2020);

    return 0;
}

int GetNumSpokenAtN(int N)
{
    return 0;
}