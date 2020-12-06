#include <string>
#include <unordered_map>
#include <vector>

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

    const std::vector<std::string> VALID_EYE_COLOURS = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };

    bool IsStringANumber(std::string& input);

};