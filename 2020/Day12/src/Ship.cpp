#include "Ship.h"
#include <Util/String.h>

Ship::Ship()
{
    m_Facing = Direction::EAST;
    m_ShipPos = { 0, 0 };
    m_WaypointPos = { 10, 1 };
}

void Ship::DoInstructionOld(std::string& instruction)
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

    //std::cout << "Instruction(" << instruction << ") takes ship (facing: " << m_Facing << ") to (" << m_ShipPos.x << "," << m_ShipPos.y << ")" << std::endl;
}

void Ship::DoInstructionNew(std::string& instruction)
{
    // this will only be 1 char anyway
    char command = instruction.substr(0, 1)[0];
    //
    int argument = atoi(instruction.substr(1).c_str());

    // do stuff to m_Pos and m_Direction based on command given
    switch (command)
    {
    case 'N':
        Translate(Direction::NORTH, argument, m_WaypointPos);
        break;
    case 'S':
        Translate(Direction::SOUTH, argument, m_WaypointPos);
        break;
    case 'E':
        Translate(Direction::EAST, argument, m_WaypointPos);
        break;
    case 'W':
        Translate(Direction::WEST, argument, m_WaypointPos);
        break;
    case 'L':
        RotateWaypoint(-argument);
        break;
    case 'R':
        RotateWaypoint(argument);
        break;
    case 'F':
        GotoWaypoint(argument);
        break;
    default:
        break;
    }

    std::cout << "Instruction(" << instruction << ")\ntakes ship to (" << m_ShipPos.x << "," << m_ShipPos.y << ")\ntakes waypoint to (" << m_WaypointPos.x << "," << m_WaypointPos.y << ")\n" << std::endl;
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
// OLD: take ship pos from waypoint pos so we can do a rotation around the origin
//      and then add it back on
// NEW: reread challenge and the waypoint is supposed to be relative to the ship,
//      so we can just treat the ship as the origin anyway
//
void Ship::RotateWaypoint(int degrees)
{
    // if we wanted the rotation to be around a point (but coordinates are in world space)
    // we can just take the point to rotate around away from our point we're rotating
    // and add it back on afterwards
    //Position originPos = m_WaypointPos - m_ShipPos;

    // may be some precision errors here
    double radians = degrees * M_PI / 180;

    // rotate around origin
    double s = std::sin(radians);
    double c = std::cos(radians);

    Position newPos;
    // this is essentially like using a 2D rotation matrix for an angle in a clockwise direction
    // [ x' ] = [  cos0, sin0  ] [ x ] = [  cos0 * x + sin0 * y  ]
    // [ y' ]   [ -sin0, cos0  ] [ y ]   [ -sin0 * x + cos0 * y  ]
    newPos.x = std::lround((m_WaypointPos.x * c) + (m_WaypointPos.y * s));
    newPos.y = std::lround((m_WaypointPos.x * -s) + (m_WaypointPos.y * c));

    m_WaypointPos = newPos;;
}
