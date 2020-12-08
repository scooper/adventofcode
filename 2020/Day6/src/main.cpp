#include <Util/File.h>
#include <Util/String.h>
#include <string>
#include <vector>
#include <iostream>

#include "Group.h"

int main()
{
    AdventCommon::File fileLoader("D:/Projects/adventofcode/2020/inputs/Day6/input.txt");
    //AdventCommon::FileLoader fileLoader("D:/Projects/adventofcode/2020/inputs/Day6/inputTest.txt");

    std::string file = fileLoader.AsStr();

    std::vector<std::string> groupStrs = AdventCommon::String::Split(file, "\n\n");

    int totalAnsweredYes = 0;
    int totalAllAnsweredYes = 0;

    for (std::string groupStr : groupStrs)
    {
        //std::cout << groupStr << "\n" << std::endl;

        Group group(groupStr);

        int questionsAnwered = group.GetNumQuestionsAnsweredYes();
        totalAnsweredYes += questionsAnwered;

        int allAnsweredYes = group.GetNumQuestionsAllAnsweredYes();
        totalAllAnsweredYes += allAnsweredYes;

        std::cout << "This group (" << group.GetMembers() << " members) answered yes to " << questionsAnwered << " questions\n"
                  "and all answered yes to " << allAnsweredYes << " questions.\n" << std::endl;

    }


    std::cout << groupStrs.size() << " groups answered yes to " << totalAnsweredYes << " questions." << std::endl;
    std::cout << "Total where group members all answered yes to same question: " << totalAllAnsweredYes << std::endl;

    return 0;
}