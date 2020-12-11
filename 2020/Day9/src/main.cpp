#include <iostream>
#include <Util/File.h>
#include <Maths/Collections.h>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day9/input.txt");
    //AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day9/inputTest.txt");

    std::vector<int> data;

    std::string line;
    while (file.NextLine(line))
    {
        data.push_back(atoi(line.c_str()));
    }

    int preamble = 25;

    int notSumOfPrevious = 0;

    for (std::vector<int>::iterator it = data.begin() + preamble; it != data.end(); it++)
    {
        std::vector<int>::iterator subit = it - preamble;
        std::vector<int> sublist(subit, it);
        
        // sort in ascending order
        std::sort(sublist.begin(), sublist.end(), [](const int& a, const int& b)
            {
                return a < b;
            });

        std::vector<int> match = AdventCommon::Collections::FindPairElementsThatSumToX<int>(sublist, *it);

        if (match.size() == 0)
        {
            std::cout << *it << " does not follow the summing rule" << std::endl;
            notSumOfPrevious = *it;
            break;
        }

    }


    std::vector<int> contiguousList = AdventCommon::Collections::FindContiguousNElementsThatSumToX(data, notSumOfPrevious);

    if (contiguousList.size() > 2)
    {
        int weakness = *std::max_element(contiguousList.begin(), contiguousList.end()) + *std::min_element(contiguousList.begin(), contiguousList.end());;
        std::cout << "Sum of min/max of list that sums to " << notSumOfPrevious << " (our 'encryption weakness') is : " << weakness << std::endl;
    }

    return 0;
}