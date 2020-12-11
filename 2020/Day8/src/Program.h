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

struct ExecutionResponse
{
    bool finished;
    int line;
    int accumulator;
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

    ExecutionResponse Execute(bool allowRepeatInstructions = false);
    int Reset();
    void ChangeLineInstructionType(int lineNum, InstructionType type);
    Line GetLine(int lineNum) { return *(m_Instructions.begin() + lineNum); };
    int Length() { return m_Instructions.size(); }
private:

    std::vector<Line>::iterator m_Position;
    int m_Accumulator;
    std::vector<Line> m_Instructions;

    InstructionResponse ProcessInstruction(bool allowRepeatInstructions);

};

