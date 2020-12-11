#include "WaitingArea.h"

WaitingArea::WaitingArea(std::vector<std::string> input)
{
    m_Length = 0;
    m_Width = 0;

    for (std::string line : input)
    {
        if (m_Width == 0)
            m_Width = line.length();

        for (char stateChar : line)
        {
            switch (stateChar)
            {
            case 'L':
                m_Chairs.push_back(ChairState::EMPTY);
                break;
            case '#':
                m_Chairs.push_back(ChairState::OCCUPIED);
                break;
            case '.': 
                m_Chairs.push_back(ChairState::FLOOR);
                break;
            }
        }

        m_Length++;
    }
}

int WaitingArea::ApplyRules()
{

    return 0;
}

ChairState WaitingArea::GetChairState(int x, int y)
{
    int i = x + (m_Width * y);
    return m_Chairs[i];
}

// count occupied states of adjacenct locations   | (x-1,y-1), (x,y-1), (x+1,y-1), (x-1,y), (x+1,y), (x-1,y+1), (x,y+1), (x+1,y+1)
// given an X and Y                               |  top left  top mid  top right    left    right    bot left  bot mid  bot right
int WaitingArea::GetNumAdjacentOccupied(int x, int y)
{
    int occupied = 0;

    for (const auto& [xMod, yMod] : ADJACENT_MODIFIERS)
    {
        int xCheck = x + xMod;
        int yCheck = y + yMod;

        ChairState state = GetChairState(xCheck, yCheck);

        if (state == ChairState::OCCUPIED)
            occupied++;
    }

    return occupied;
}
