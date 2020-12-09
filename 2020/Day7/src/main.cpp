#include <Util/File.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <Util/String.h>

#include "Bag.h"

int main()
{


    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day7/input.txt");

    std::unordered_map<std::string, Bag> bagMap;

    std::string line;


    // first pass (populate the map)
    while (file.NextLine(line))
    {
        std::vector<std::string> split = AdventCommon::String::Split(line, " bags contain ");

        std::string bagStr = split[0];

        Bag bag(bagStr);

        bagMap[bag.m_Key] = bag;

    }

    // reset file (because right now we're at the end of file)
    file.Reset();

    // second pass (populate Bag parents and children with bags in the map)
    while (file.NextLine(line))
    {
        std::vector<std::string> split = AdventCommon::String::Split(line, " bags contain ");

        std::string bagStr = split[0];
        std::string ruleStr = split[1];

        auto ruleSplit = AdventCommon::String::Split(ruleStr, ", ");

        for (std::string rule : ruleSplit)
        {
            if (rule.find("no other") != std::string::npos)
                break;

            auto sections = AdventCommon::String::Split(rule, " ");

            // extract number
            int quant = std::atoi(sections[0].c_str());

            // extract key
            std::string key = sections[1] + " " + sections[2];

            bagMap[bagStr].AddChild(&bagMap[key], quant);
            bagMap[key].AddParent(&bagMap[bagStr]);
        }
    }

    std::string searchBag = "shiny gold";

    std::vector<Bag*> shinyGoldParentBags;
    bagMap[searchBag].GetAllParentsRecursive(shinyGoldParentBags);

    int shinyContentsNum = 0;

    bagMap[searchBag].GetAllChildrenRecursive(shinyContentsNum);




    std::cout << "Num Bags that can contain a '" << searchBag << "' : " << shinyGoldParentBags.size() << std::endl;
    std::cout << "Num Bags that have to be inside a '" << searchBag << "' : " << shinyContentsNum << std::endl;

    /*for (Bag* bag : shinyGoldParentBags)
    {
        std::cout << bag->m_Key << std::endl;
    }*/

    return 0;
}