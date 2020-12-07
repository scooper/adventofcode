#pragma once
#include <string>
#include <vector>

class BoardingPass
{
public:
    BoardingPass(std::string bsp);
    int GetSeatID() { return m_SeatID; }
    int GetRow() { return m_Row; }
    int GetColumn() { return m_Column; }

private:
    int m_SeatID;
    int m_Row;
    int m_Column;
    int RecursiveSearch(int min, int max, std::string::iterator it, std::string::const_iterator end);

};

struct Seat
{
    int row;
    int column;
    int id;
    BoardingPass* occupant;
};

class Plane
{
public:
    Plane();

    void OccupySeat(BoardingPass* pass);
    std::vector<Seat> GetEmptySeats();
private:
    const int ROWS = 128;
    const int COLUMNS = 8;

    std::vector<Seat> m_Seats;
};