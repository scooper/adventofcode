#include <Util/FileLoader.h>
#include <string>
#include <vector>
#include <iostream>

class SlopeData
{
public:
    SlopeData(const char* filepath) { Load(filepath); }
    char Get(int x, int y);

private:
    std::vector<char> m_Data;
    int m_Width;
    int m_Height;

    void Load(const char* filepath);
};


// gets data from our data based on cartesian coordinate system from x=0 to positive x and y=0 to negative y
char SlopeData::Get(int x, int y)
{
    // map 2D coordinates to 1D array
    int i = (x % m_Width) + m_Width * (y*-1);

    std::cout << "X=" << x << " Y=" << y << std::endl;
    std::cout << "Array Index=" << i << std::endl;
    std::cout << "Char=" << m_Data[i] << std::endl;
    return m_Data[i];
}

void SlopeData::Load(const char* filepath)
{
    AdventCommon::FileLoader fileLoader(filepath);

    // initialise
    m_Height = 0;
    m_Width = 0;
    std::string line;
    while (fileLoader.NextLine(line))
    {
        if (m_Width == 0)
            m_Width = (int)line.length();

        for(char c: line)
            m_Data.push_back(c);

        m_Height++;
    }

    std::cout << "Width: " << m_Width << ", Height: " << m_Height << std::endl;
}

int main()
{
    SlopeData slope("D:/Projects/adventofcode/2020/inputs/Day3/input.txt");

    slope.Get(1, -1);
    slope.Get(1, -322);
    slope.Get(30, -322);

    return 0;
}