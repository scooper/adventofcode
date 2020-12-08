#include <Util/File.h>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

struct Gradient
{
    int right;
    int down;
};

class SlopeData
{
public:
    SlopeData(const char* filepath) { Load(filepath); }
    char Get(int x, int y);
    int GetCharIntersectionsForGradient(Gradient gradient, char characterToCheck);

private:
    std::vector<char> m_Data;
    int m_Width;
    int m_Height;
    void Load(const char* filepath);
};


// gets data from our data based on cartesian coordinate system from x=0 to positive x and y=0 to negative y
char SlopeData::Get(int x, int y)
{
    // TODO: error checking for non natural numbers? because it will break indexing
    // though it'd be truncated anyway below

    // map 2D coordinates to 1D array
    int i = (x % m_Width) + m_Width * (y*-1);

    return m_Data[i];
}

// gets the number of intersections of the give character for the line produced by the given gradient
int SlopeData::GetCharIntersectionsForGradient(Gradient gradient, char characterToCheck)
{
    // negate gradient for resulting line to be from top left to bottom right
    double m = ((double)gradient.down / gradient.right) * -1; // gradient (doing gradients like this may break down in some cases due to floating point errors)

    int intersections = 0;

    // iterate the y axis in a negative direction
    for (int y = 0; y > (m_Height * -1); y--)
    {
        // calculate x
        double x = y / m;

        double fractionalPart;

        // dont bother computing fractional X values
        if (modf(x, &fractionalPart) != 0)
            continue;

        char charAtX = Get(x, y);
        if (charAtX == characterToCheck)
            intersections++;

    }
    return intersections;
}

void SlopeData::Load(const char* filepath)
{
    AdventCommon::File fileLoader(filepath);

    // initialise
    m_Height = 0;
    m_Width = 0;
    std::string line;

    // build buffer
    while (fileLoader.NextLine(line))
    {
        if (m_Width == 0)
            m_Width = (int)line.length();

        for(char c: line)
            m_Data.push_back(c);

        m_Height++;
    }
}

int main()
{
    SlopeData slope("D:/Projects/adventofcode/2020/inputs/Day3/input.txt");

    // list of gradients to check
    std::vector<Gradient> gradients = { {1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2} };

    char characterToCheck = '#';

    // could result in big number
    long long productOfIntersections = 0;

    for (Gradient gradient: gradients)
    {
        int intersections = slope.GetCharIntersectionsForGradient(gradient, characterToCheck);
        std::cout << "Intersections on gradient right=" << gradient.right << ", down=" << gradient.down << " : " << intersections << std::endl;

        // calculate product
        if (productOfIntersections == 0)
            productOfIntersections = intersections;
        else
            productOfIntersections *= intersections;
    }

    std::cout << "Product of intersections : " << productOfIntersections << std::endl;


    return 0;
}
