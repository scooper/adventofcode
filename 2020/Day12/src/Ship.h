#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

struct Position
{
    int x;
    int y;

    Position& operator +(const Position& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Position& operator -(const Position& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Position& operator +=(const Position& other)
    {
        *this = *this + other;
        return *this;
    }

    Position& operator -=(const Position& other)
    {
        *this = *this - other;
        return *this;
    }
};

enum Direction
{
    NORTH = 0,
    EAST = 90,
    SOUTH = 180,
    WEST = 270
};

class Ship
{
public:
    Ship();

    void DoInstruction(std::string& instruction);

    int GetManhattanDistance() { return std::abs(m_ShipPos.x) + std::abs(m_ShipPos.y); }

private:
    Direction m_Facing;
    Position m_ShipPos;
    Position m_WaypointPos;

    void Translate(Direction dir, int units, Position& pos);
    void GotoWaypoint(int iterations);
    void RotateShip(int degrees);
    void RotateWaypoint(int degrees);
};

