#include <iostream>
#include <fstream>
#include <sstream>
#include <regex> // I'll leave this here because I tried to use you but you're a bitch
#include <vector>
#include <Util/FileLoader.h>

struct Policy
{
    char character;
    int min;
    int max;
};

// declarations
bool IsPasswordValidOld(std::string password, Policy policy);
bool IsPasswordValidNew(std::string password, Policy policy);
std::vector<int> ExtractNumsFromString(std::string input);

int main()
{
    AdventCommon::FileLoader fileLoader("D:/Projects/adventofcode/2020/inputs/Day2/input.txt");

    int validPasswordsOld = 0, validPasswordsNew = 0;

    std::string line;
    while (fileLoader.NextLine(line))
    {
        // get colon location
        size_t colonIndex = line.find(":");

        // get password which should be offset from the colon
        std::string password = line.substr(colonIndex + 2);

        // get just the policy which is everything before the colon
        std::string policy = line.substr(0, colonIndex);

        // the end of the policy should be the character, -1 because of the null terminator
        char c = *(policy.end()-1);

        // get the min and max
        std::vector<int> nums = ExtractNumsFromString(policy);

        // check validity
        if (IsPasswordValidOld(password, { c, nums[0], nums[1] }))
            validPasswordsOld++;
        if (IsPasswordValidNew(password, { c, nums[0], nums[1] }))
            validPasswordsNew++;

    }

    std::cout << "Num Valid Passwords (old): " << validPasswordsOld << std::endl;
    std::cout << "Num Valid Passwords (new): " << validPasswordsNew << std::endl;

    return 0;
}

// returns true if the password meets the policy requirements (of the sled rental place down the street)
bool IsPasswordValidOld(std::string password, Policy policy)
{
    int numOccurances = 0;

    for (int i = 0; i < password.length(); i++)
    {
        char c = password[i];
        if (c == policy.character)
            numOccurances++;
    }

    if (numOccurances > policy.max || numOccurances < policy.min)
        return false;
    else
        return true;
}

// returns true if the password meets the policy requirements (of the Official Toboggan Corporate Policy)
bool IsPasswordValidNew(std::string password, Policy policy)
{
    char firstPosition = password[(int)(policy.min-1)];
    char secondPosition = password[(int)(policy.max-1)];

    if ((firstPosition == policy.character) ^ (secondPosition == policy.character))
        return true;
    else
        return false;
}


// returns a vector of int for the numbers contained in a string, in the order they appear from left to right
std::vector<int> ExtractNumsFromString(std::string input)
{
    std::vector<int> nums;
    std::stringstream numberBuffer;

    for (int i = 0; i < input.length(); i++)
    {
        // extract char
        char c = input[i];

        if (isdigit(c))
        {
            // add the valid digit to the buffer
            numberBuffer << c;
        }
        else
        {
            std::string number = numberBuffer.str();

            // in some cases we may get an empty string so check for this to avoid error
            if (!number.empty())
                nums.push_back(atoi(number.c_str()));

            // reset stringstream
            numberBuffer.str(std::string());
            numberBuffer.clear();
        }
    }

    return nums;
}