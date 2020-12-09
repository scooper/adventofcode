//
// Various common string manipulation/validation functions
//
#pragma once

#include <vector>
#include <string>

namespace AdventCommon
{
    // NOTE: possibly a bit misleaing calling this string because it doesn't implement a string,
    // just has a few convenience functions (maybe rename StringHelper?)
    class String
    {
    public:
        static std::vector<std::string> Split(std::string input, std::string delimiter);
        static std::string Join(std::vector<std::string>& input, std::string delimiter);
        static bool IsNumber(std::string& input);
    };
}
