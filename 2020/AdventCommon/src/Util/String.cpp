#include "String.h"

namespace AdventCommon
{
    // returns a collection of strings split at the given delimiter, in the order they
    // are encountered from left to right
    std::vector<std::string> String::Split(std::string input, std::string delimiter)
    {
        std::vector<std::string> stringys;

        size_t spaceLoc = 0;

        // basically do a string split but a really fucky way (because c++)
        while ((spaceLoc = input.find(delimiter)) != std::string::npos)
        {
            std::string token = input.substr(0, spaceLoc);
            input.erase(0, spaceLoc + delimiter.length());

            stringys.push_back(token);
        }
    
        // should be the last bit of string after the last delimiter
        if(!input.empty())
            stringys.push_back(input);

        return stringys;
    }

    // Returns true if given string is a number (specifically a number with no fractional part)
    bool String::IsNumber(std::string& input)
    {
        // lambdas and shit yo
        // we're finding all non digits and seeing if the result is the end of the iterator
        // in which case we've exhausted the string so it must be a number!
        return !input.empty() && std::find_if(input.begin(), input.end(), [](unsigned char c) { return !std::isdigit(c); }) == input.end();
    }
}
