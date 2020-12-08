#include <Util/File.h>
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <regex> // *sigh* ... you again

#include "Passport.h"



int main()
{
    AdventCommon::File fileLoader("D:/Projects/adventofcode/2020/inputs/Day4/input.txt");

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