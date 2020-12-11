#include <Util/File.h>
#include <Util/String.h>
#include <string>
#include <vector>
#include <iostream>

#include "Program.h"

int main()
{
    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day8/input.txt");
    //AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day8/inputTest.txt");

    std::vector<std::string> input = AdventCommon::String::Split(file.AsStr(), "\n");
    
    Program program(input);

    for (std::string instruction : input)
    {
        std::cout << instruction << std::endl;
    }

    program.Execute();
    int last = program.Reset();

   /* ,===============================================================,
    |               |  |        ||         ||| |_  . / \            | 
    |               |  |_____   ||         ||| \ n\V/0  \           |
    |              .de@@@@@@@@bee|         ||| [brute force]        |
    |           .d@@@@@@@4/^^J4@@=---....__l||    `(_|\_)           |
    |          .d@@@@PJP.=- .--4||""**==---,||                      |
    |          |@P**@==[-"0]=['0]|         |||                      |
    |          \@:'5"       .5 '||         |||                      |
    |           )@b..      <6d .||    ,='D |||                      |
    |            Z\( `._     ^ P'l.._/ /___|||. _                   |
    |           |=-L--.._ `*=r'7.| 7   """`..-=eE'                  |
    |   _______x'--._ `v'I   |    Y         _;P*"   .._.'.*^.,_     |
    | /`    `'.   \  `.  J-..-'-v`    . '` |||    _.S          'c   |
    |'         |   ',  '. '-_-'/     A'--..|||   '^,  .'         {_'|
    |        /  -.   \   '-._.'_    A7\ M/,--..``''7                |
    |     -'.-""= \   L  ./`     '\| \                              |
    |   '.'        \.-;'   [Is this a good algorithm?]              |
    `==============================================================='*/
    for (int i = 0; i < program.Length(); i++)
    {
        // first line
        Line line = program.GetLine(i);

        // switch NOP with JMP
        if (line.instruction == NOP)
        {
            program.ChangeLineInstructionType(i, JMP);
        }
        else if (line.instruction == JMP)
        {
            program.ChangeLineInstructionType(i, NOP);
        }

        ExecutionResponse ex = program.Execute();

        if(ex.finished)
        {
            std::cout << "Program successfully finished" << std::endl;
            break;
        }
        else
        {
            // switch NOP with JMP
            if (line.instruction == NOP)
            {
                program.ChangeLineInstructionType(i, NOP);
            }
            else if (line.instruction == JMP)
            {
                program.ChangeLineInstructionType(i, JMP);
            }
        }

        program.Reset();
    }

    return 0;
}

