#include "Ship.h"
#include <Util/String.h>

Ship::Ship()
{
    m_Facing = Direction::EAST;
    m_ShipPos = { 0, 0 };
    m_WaypointPos = { 10, 1 };
}

void Ship::DoInstruction(std::string& instruction)
{
    // this will only be 1 char anyway
    char command = instruction.substr(0, 1)[0];
    //
    int argument = atoi(instruction.substr(1).c_str());

    // do stuff to m_Pos and m_Direction based on command given
    switch (command)
    {
    case 'N':
        Translate(Direction::NORTH, argument, m_ShipPos);
        break;
    case 'S':
        Translate(Direction::SOUTH, argument, m_ShipPos);
        break;
    case 'E':
        Translate(Direction::EAST, argument, m_ShipPos);
        break;
    case 'W':
        Translate(Direction::WEST, argument, m_ShipPos);
        break;
    case 'L':
        RotateShip(-argument);
        break;
    case 'R':
        RotateShip(argument);
        break;
    case 'F':
        Translate(m_Facing, argument, m_ShipPos);
        break;
    default:
        break;
    }

    std::cout << "Instruction(" << instruction << ") takes ship (facing: " << m_Facing << ") to (" << m_ShipPos.x << "," << m_ShipPos.y << ")" << std::endl;
}

void Ship::Translate(Direction dir, int units, Position& pos)
{
    switch (dir)
    {
    case NORTH:
        pos.y += units;
        break;
    case EAST:
        pos.x += units;
        break;
    case SOUTH:
        pos.y -= units;
        break;
    case WEST:
        pos.x -= units;
        break;
    default:
        break;
    }
}

void Ship::GotoWaypoint(int iterations)
{
    for (int i = 0; i < iterations; i++)
    {
        m_ShipPos += m_WaypointPos;
    }
}

void Ship::RotateShip(int degrees)
{
    int calc = m_Facing + degrees;

    int mod = calc % 360;

    if (mod < 0)
        mod += 360;

    // should force degrees to a 0 - 359 range
    m_Facing = (Direction)mod;
}


// TODO: - generalise this?
//       - put it in a math library
//
// take ship pos from waypoint pos so we can do a rotation around the origin
// and then add it back on
void Ship::RotateWaypoint(int degrees)
{
    // limit degrees to a 0 to 359 range
    degrees = degrees % 360;

    if (degrees < 0)
        degrees += 360;

    Position originPos = m_WaypointPos - m_ShipPos;

    // may be some precision errors here
    double radians = degrees * 3.14 / 180;

    // rotate around origin
    int s = std::round(std::sin(radians));
    int c = std::round(std::cos(radians));

    originPos.x = (originPos.x * c) + (originPos.y * -s);
    originPos.y = (originPos.x * s) + (originPos.y * c);

    m_WaypointPos = originPos + m_ShipPos;
}
