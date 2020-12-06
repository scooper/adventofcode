#include "Passport.h"
#include <iostream>
#include <algorithm>
#include <cctype>
#include <regex> // hello darkness my old friend

Passport::Passport(std::string credentialDump)
{
    size_t spaceLoc = 0;

    // basically do a string split but a really fucky way
    while ((spaceLoc = credentialDump.find(" ")) != std::string::npos)
    {
        std::string token = credentialDump.substr(0, spaceLoc);
        credentialDump.erase(0, spaceLoc + 1);

        // split the token where the colon is so we get a key and value
        size_t colonLoc = token.find(":");
        std::string field = token.substr(0, colonLoc);
        std::string value = token.substr(colonLoc + 1);

        credentials[field] = value;
    }

}

bool Passport::AllFieldsPresent()
{
    for (auto const& [key, value] : REQUIRED_FIELDS)
    {
        // check if any are not present
        if (credentials.find(key) == credentials.end())
            return false;
    }

    return true;
}

// this is a bit stanky, needs some big work
// maybe use regex
bool Passport::AllFieldsValid()
{
    bool valid = true;

    // c++ 17 babyyyy
    for (auto const& [key, value] : credentials)
    {
        std::string input = value;
        if (REQUIRED_FIELDS.find(key) == REQUIRED_FIELDS.end())
            continue;

        FieldType field = REQUIRED_FIELDS.at(key);
        switch (field)
        {
        case BirthYear:
        {
            if (IsStringANumber(input))
            {
                int value = atoi(input.c_str());
                if (value < 1920 || value > 2002)
                    valid = false;
            }
            else
            {
                valid = false;
            }
            break;
        }
        case IssueYear:
        {
            if (IsStringANumber(input))
            {
                int value = atoi(input.c_str());
                if (value < 2010 || value > 2020)
                    valid = false;
            }
            else
            {
                valid = false;
            }
            break;
        }
        case ExpirationYear:
        {
            if (IsStringANumber(input))
            {
                int value = atoi(input.c_str());
                if (value < 2020 || value > 2030)
                    valid = false;
            }
            else
            {
                valid = false;
            }
            break;
        }
        case Height:
        {
            std::string unit = input.substr(input.length()-2);
            std::string heightValStr = input.substr(0, input.length() - 2);

            if (IsStringANumber(heightValStr) == false)
                valid = false;

            int heightVal = atoi(heightValStr.c_str());

            if (unit == "cm")
            {
                if (heightVal < 150 || heightVal > 193)
                    valid = false;
            }
            else if(unit == "in")
            {
                if (heightVal < 59 || heightVal > 76)
                    valid = false;
            }
            else
            {
                valid = false;
            }

            break;
        }
        case HairColour:
        {
            if (!std::regex_match(input, std::regex("#[a-fA-F0-9]{6}")))
                valid = false;

            break;
        }
        case EyeColour:
        {
            if (std::find(VALID_EYE_COLOURS.begin(), VALID_EYE_COLOURS.end(), input) == VALID_EYE_COLOURS.end())
                valid = false;

            break;
        }
        case PassportId:
        {
            if (IsStringANumber(input))
            {
                if(input.length() != 9)
                    valid = false;
            }
            else
            {
                valid = false;
            }
            break;
        }
        default:
            continue;
        }
    }

    return valid;
}

// TODO: put this in AdventCommon?
bool Passport::IsStringANumber(std::string& input)
{
    // lambdas and shit yo
    // we're finding all non digits and seeing if the result is the end of the iterator
    // in which case we've exhausted the string so it must be a number!
    return !input.empty() && std::find_if(input.begin(), input.end(), [](unsigned char c) { return !std::isdigit(c); }) == input.end();
}


