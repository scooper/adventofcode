#include "Seat.h"
#include <iostream>
#include <algorithm>

BoardingPass::BoardingPass(std::string bsp)
{
    std::string rowString = bsp.substr(0, bsp.length() - 3);
    std::string colString = bsp.substr(bsp.length() - 3);

    //std::cout << rowString << " " << colString << std::endl;

    m_Row = RecursiveSearch(0, 127, rowString.begin(), rowString.end());
    m_Column = RecursiveSearch(0, 7, colString.begin(), colString.end());

    m_SeatID = (m_Row * 8) + m_Column;

    //std::cout << m_Row << " " << m_Column << std::endl;
}

int BoardingPass::RecursiveSearch(int min, int max, std::string::iterator it, std::string::const_iterator end)
{
    int half = (min + max + 1) / 2;

    bool oneAway = max - min == 1;

    if (it == end)
    {
        return -1;
    }

    if (*it == 'F' || *it == 'L')
    {
        if (oneAway)
            return min;

        return RecursiveSearch(min, half-1, ++it, end);
    }
    else if (*it == 'B' || *it == 'R')
    {
        if (oneAway)
            return max;

        return RecursiveSearch(half, max, ++it, end);
    }

    return -1;
}

Plane::Plane()
{
    // initialise an empty plane
    for (int y = 0; y < COLUMNS; y++)
    {
        for (int x = 0; x < ROWS; x++)
        {
            m_Seats.push_back({ x, y, (x * 8) + y, nullptr });
        }
    }
}

void Plane::OccupySeat(BoardingPass* pass)
{
    int i = pass->GetRow() + (ROWS * pass->GetColumn());

    m_Seats[i].occupant = pass;
}

std::vector<Seat> Plane::GetEmptySeats()
{
    std::vector<Seat> emptySeats;
    for (Seat seat : m_Seats)
    {
        if (seat.occupant == nullptr)
        {
            emptySeats.push_back(seat);
        }
    }

    return emptySeats;
}
