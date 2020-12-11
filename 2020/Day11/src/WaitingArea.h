#pragma once
#include <vector>
#include <string>

enum class ChairState
{
    FLOOR,
    EMPTY,
    OCCUPIED
};

class WaitingArea
{
public:
    WaitingArea(std::vector<std::string> input);
    int ApplyRules();

private:
    ChairState GetChairState(int x, int y);
    int GetNumAdjacentOccupied(int x, int y);
    int m_Width;
    int m_Length;
    std::vector<ChairState> m_Chairs;

    const std::vector<std::pair<int, int>> ADJACENT_MODIFIERS = { {-1,-1},{0,-1},{1,-1},{-1,0},{1,0},{-1,1},{0,1},{1,1} };
};

