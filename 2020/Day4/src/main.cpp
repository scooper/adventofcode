#include <Util/FileLoader.h>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
#include <iostream>
#include <regex> // *sigh* ... you again

enum FieldType
{
    BirthYear,
    IssueYear,
    ExpirationYear,
    Height,
    HairColour,
    EyeColour,
    PassportId,
    CountryId
};

class Passport
{
public:
    Passport(std::string credentialDump);
    bool AllFieldsPresent();
    bool AllFieldsValid();
private:
    // one to hold the credential type and one to show whether it is missing
    std::unordered_map<std::string, std::string> credentials;

    // the other field which we're omitting is 'cid'
    const std::unordered_map<std::string, FieldType> REQUIRED_FIELDS = { {"byr", BirthYear}, {"iyr", IssueYear}, {"eyr", ExpirationYear},
                                                                         {"hgt", Height}, {"hcl", HairColour}, {"ecl", EyeColour}, {"pid", PassportId} };

};

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
        std::string value = token.substr(colonLoc+1);

        credentials[field] = value;
    }

}

bool Passport::AllFieldsPresent()
{
    for (auto const& [key, value]: REQUIRED_FIELDS)
    {
        // check if any are not present
        if (credentials.find(key) == credentials.end())
            return false;
    }

    return true;
}

bool Passport::AllFieldsValid()
{
    bool valid = true;

    // c++ 17 babyyyy
    for (auto const& [key, value] : credentials)
    {
        if (REQUIRED_FIELDS.find(key) == REQUIRED_FIELDS.end())
            continue;

        FieldType field = REQUIRED_FIELDS.at(key);
        switch (field)
        {
        case BirthYear:
            
            break;
        case IssueYear:
            break;
        case ExpirationYear:
            break;
        case Height:
            break;
        case HairColour:
            break;
        case EyeColour:
            break;
        case PassportId:
            break;
        default:
            break;
        }
    }

    return false;
}

int main()
{
    AdventCommon::FileLoader fileLoader("D:/Projects/adventofcode/2020/inputs/Day4/input.txt");

    // one to hold the credential type and one to show whether it is missing

    std::string line;
    std::stringstream buffer;

    int totalPassports = 0;
    int totalPresentFieldsPassports = 0;
    int totalValidPassports = 0;
    int totalPresentAndValidPassports = 0;

    // build passports and check validity (using a class for convenience, and discarding the actual object -
    // but we could keep if we wanted)
    while (fileLoader.NextLine(line))
    {

        if (line.empty())
        {
            Passport passport(buffer.str());
            if (passport.AllFieldsPresent())
                totalPresentFieldsPassports++;

            if (passport.AllFieldsValid())
                totalValidPassports++;

            if (passport.AllFieldsValid() && passport.AllFieldsPresent())
                totalPresentAndValidPassports++;

            totalPassports++;
            buffer.str(std::string());
            buffer.clear();
        }
        else
        {
            buffer << line + " ";
        }
        
    }

    // buffer is still full after loop if there is no new line at the end of the file
    // (should really change this as its a bit shit)
    std::string finalData = buffer.str();
    if (!finalData.empty())
    {
        Passport passport(finalData);
        if (passport.AllFieldsPresent())
            totalPresentFieldsPassports++;

        if (passport.AllFieldsValid())
            totalValidPassports++;

        if (passport.AllFieldsValid() && passport.AllFieldsPresent())
            totalPresentAndValidPassports++;

        totalPassports++;
    }
    
    std::cout << "Num Passports with required fields present: " << totalPresentFieldsPassports << "/" << totalPassports << std::endl;
    std::cout << "Num Passports with valid data: " << totalValidPassports << "/" << totalPassports << std::endl;
    std::cout << "Num Passports with valid data and fields present: " << totalPresentAndValidPassports << "/" << totalPassports << std::endl;
    return 0;
}