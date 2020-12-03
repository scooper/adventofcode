#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <Util/FileLoader.h>

std::vector<int> findPairIntsThatSumToX(std::vector<int>& numbers, int x);
std::vector<int> find3IntsThatSumToX(std::vector<int>& numbers, int x);

int main()
{

    AdventCommon::FileLoader fileLoader("D:/Projects/adventofcode/2020/inputs/Day1/input.txt");

    std::vector<int> numbers;

    std::string line;

    // build a vector of int
    while (fileLoader.NextLine(line))
    {
        numbers.push_back(std::atoi(line.c_str()));
    }

    // sort in ascending order
    std::sort(numbers.begin(), numbers.end(), [](const int &a, const int &b)
        {
            return a < b;
        });

    std::vector<int> resultNums = find3IntsThatSumToX(numbers, 2020);
    int resultSize = resultNums.size();

    if (resultSize > 0)
    {
        int product = 0;
        for (int i = 0; i < resultSize; i++)
        {
            std::cout << "Num " << i << " = " << resultNums[i] << std::endl;
            if (i == 0)
                product = resultNums[0];
            else
                product *= resultNums[i];
        }
        std::cout << "Product = " << product << std::endl;
    }

    return 0;
}

// TODO: this is a bit shit - would be nice to be able to specify any N for the amount of numbers to find and multiply in the list
std::vector<int> find3IntsThatSumToX(std::vector<int> &numbers, int x)
{
    std::vector<int> desiredNums;

    for (int i = 0; i < numbers.size(); i++)
    {
        int target = x - numbers[i];
        std::vector<int> result = findPairIntsThatSumToX(numbers, target);
        desiredNums.insert(desiredNums.begin(), result.begin(), result.end());

        if (desiredNums.size() == 2)
        {
            desiredNums.push_back(numbers[i]);
            return desiredNums;
        }
    }

    return desiredNums;
}

std::vector<int> findPairIntsThatSumToX(std::vector<int> &numbers, int x)
{
    // go from the front of the sorted set and backwards from the end of the set, checking for a sum
    std::vector<int> desiredNums;
    bool foundMatch = false;
    // find the match
    for (int front = 0, back = numbers.size() - 1; front < back;)
    {
        int total = numbers[front] + numbers[back];
        if (total > x)
        {
            back--;
        }
        else if (total < x)
        {
            front++;
        }
        else
        {
            // yay
            desiredNums.push_back(numbers[front]);
            desiredNums.push_back(numbers[back]);
            foundMatch = true;
            break;
        }
    }

    return desiredNums;
}