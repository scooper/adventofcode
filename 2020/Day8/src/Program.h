#pragma once
#include <string>
#include <vector>
#include <Util/String.h>

enum InstructionType
{
    NOP,
    ACC,
    JMP
};

struct InstructionResponse
{
    bool success;
    int line;
    std::string comment;
};


struct Line
{
    InstructionType instruction;
    int argument;
    bool executed;
};

class Program
{
public:
    Program(std::vector<std::string> instructions);

    void Execute(bool allowRepeatInstructions = false);
    int Reset();
    void ChangeLineInstructionType(int lineNum, InstructionType type);
private:

    std::vector<Line>::iterator m_Position;
    int m_Accumulator;
    std::vector<Line> m_Instructions;

    InstructionResponse ProcessInstruction(bool allowRepeatInstructions);

};

