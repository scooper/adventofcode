#include "File.h"
#include <iostream>
#include <fstream>

namespace AdventCommon
{

    File::File(const char* filepath)
    {
        std::ifstream fileStream;

        fileStream.open(filepath);

        if (fileStream.is_open())
        {
            m_Buffer << fileStream.rdbuf();
            fileStream.close();
            std::cout << "Loaded: " << filepath << std::endl;
            fileStream.close();
        }
        else
        {
            std::cout << "Something went wrong loading the file" << std::endl;
        }

    }

    File::~File()
    {
    }

    // allows you to retrieve file contents, line by line until the end of file
    bool File::NextLine(std::string &line)
    {
        bool isLine = (bool)std::getline(m_Buffer, line);
        return isLine;

    }

    // resets the file to the start and clears any flags set (error, eof)
    // this means you may call the NextLine function again
    void File::Reset()
    {
        m_Buffer.clear();
        m_Buffer.seekg(0);
    }

}
