#include "WaitingArea.h"

#include <iostream>

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
            default:
                m_Chairs.push_back(ChairState::INVALID);
                break;
            }
        }

        m_Length++;
    }
}

int WaitingArea::ApplyOldRules()
{
    bool vecDiff = true;

    while (vecDiff)
    {
        std::vector<ChairState> temp;

        for (int y = 0; y < m_Length; y++)
        {
            for (int x = 0; x < m_Width; x++)
            {
                ChairState state = GetChairState(x, y);
                int occupied = GetNumAdjacentOccupied(x, y);

                if (state == ChairState::EMPTY && occupied == 0)
                {
                    temp.push_back(ChairState::OCCUPIED);
                }
                else if (state == ChairState::OCCUPIED && occupied >= 4)
                {
                    temp.push_back(ChairState::EMPTY);
                }
                else
                {
                    temp.push_back(state);
                }
            }
        }


        if (std::equal(m_Chairs.begin(), m_Chairs.end(), temp.begin()))
            vecDiff = false;
        else
            m_Chairs = temp;
    }

    return GetNumOccupied();
}

int WaitingArea::ApplyNewRules()
{
    bool vecDiff = true;

    while (vecDiff)
    {
        std::vector<ChairState> temp;

        for (int y = 0; y < m_Length; y++)
        {
            for (int x = 0; x < m_Width; x++)
            {
                ChairState state = GetChairState(x, y);
                int occupied = GetNumVisibleOccupied(x, y);

                if (state == ChairState::EMPTY && occupied == 0)
                {
                    temp.push_back(ChairState::OCCUPIED);
                }
                else if (state == ChairState::OCCUPIED && occupied >= 5)
                {
                    temp.push_back(ChairState::EMPTY);
                }
                else
                {
                    temp.push_back(state);
                }
            }
        }


        if (std::equal(m_Chairs.begin(), m_Chairs.end(), temp.begin()))
            vecDiff = false;
        else
            m_Chairs = temp;
    }

    return GetNumOccupied();
}

ChairState WaitingArea::GetChairState(int x, int y)
{
    int i = x + (m_Width * y);

    // invalid x or y
    if (i >= m_Chairs.size() ||
        x < 0 ||
        y < 0 ||
        x >= m_Width ||
        y >= m_Length)
        return ChairState::INVALID;

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

int WaitingArea::GetNumVisibleOccupied(int x, int y)
{
    int occupied = 0;

    for (const auto& [xMod, yMod] : ADJACENT_MODIFIERS)
    {
        int xCheck = x;
        int yCheck = y;

        int found = false;

        while (!found)
        {
            xCheck += xMod;
            yCheck += yMod;

            ChairState state = GetChairState(xCheck, yCheck);

            if (state == ChairState::OCCUPIED)
            {
                occupied++;
            }

            if (state == ChairState::EMPTY || state == ChairState::INVALID || state == ChairState::OCCUPIED)
            {
                found = true;
            }
        }
        
    }

    return occupied;
}

int WaitingArea::GetNumOccupied()
{
    int occupied = 0;

    for (ChairState state : m_Chairs)
    {
        if (state == ChairState::OCCUPIED)
            occupied++;
    }

    return occupied;
}
