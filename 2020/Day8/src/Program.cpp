#include "Program.h"
#include <iostream>


Program::Program(std::vector<std::string> instructions)
{
    m_Accumulator = 0;

    for (std::string instruction : instructions)
    {
        std::vector<std::string> split = AdventCommon::String::Split(instruction, " ");
        
        Line line;
        line.executed = false;

        if (split[0] == "nop")
            line.instruction = NOP;
        else if (split[0] == "acc")
            line.instruction = ACC;
        else if (split[0] == "jmp")
            line.instruction = JMP;

        char sign = *split[1].begin();
        int number = atoi(split[1].substr(1).c_str());
        if (sign == '-')
            line.argument = -1 * number;
        else
            line.argument = number;

        m_Instructions.push_back(line);
    }

    m_Position = m_Instructions.begin();
}

ExecutionResponse Program::Execute(bool allowRepeatInstructions)
{
    bool running = true;
    bool finished = true;
    InstructionResponse response;
    while (running)
    {
        response = ProcessInstruction(allowRepeatInstructions);

        if (!response.success)
        {
            std::cout << response.comment << " at line " << response.line << std::endl;
            break;
        }

    }

    ExecutionResponse execResponse = { false, response.line, m_Accumulator };

    if (response.line == -1)
        execResponse.finished = true;

    std::cout << "Accumulator ended at: " << m_Accumulator << std::endl;

    return execResponse;
}

int Program::Reset()
{
    int linesExecuted = 0;
    for (std::vector<Line>::iterator it = m_Instructions.begin(); it != m_Instructions.end(); it++)
    {
        if ((*it).executed == true)
            linesExecuted++;

        (*it).executed = false;
    }

    m_Position = m_Instructions.begin();
    m_Accumulator = 0;
    return linesExecuted;
}

void Program::ChangeLineInstructionType(int lineNum, InstructionType type)
{
    (*(m_Instructions.begin() + lineNum)).instruction = type;
}

InstructionResponse Program::ProcessInstruction(bool allowRepeatInstructions)
{
    if (m_Position == m_Instructions.end())
    {
        return { false, -1, "end of program" };
    }
    
    int lineNumber = m_Position - m_Instructions.begin();

    if ((*m_Position).executed && !allowRepeatInstructions)
    {
        return { false, lineNumber, "instruction has already been executed" };
    }

    (*m_Position).executed = true;

    switch ((*m_Position).instruction)
    {
    case NOP:
        m_Position++;
        break;
    case ACC:
        m_Accumulator += (*m_Position).argument;
        m_Position++;
        break;
    case JMP:
        m_Position += (*m_Position).argument;
        break;
    }


    return { true, lineNumber, "" };
}
