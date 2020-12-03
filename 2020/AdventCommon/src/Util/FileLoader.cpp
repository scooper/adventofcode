#include "FileLoader.h"
#include <iostream>
#include <fstream>

namespace AdventCommon
{

    FileLoader::FileLoader(const char* filepath)
    {
        std::ifstream fileStream;

        fileStream.open(filepath);

        if (fileStream.is_open())
        {
            m_Buffer << fileStream.rdbuf();
            fileStream.close();
            std::cout << "Loaded: " << filepath << std::endl;
        }
        else
        {
            std::cout << "Something went wrong loading the file" << std::endl;
        }

    }

    FileLoader::~FileLoader()
    {
    }

    bool FileLoader::NextLine(std::string &line)
    {
        bool isLine = (bool)std::getline(m_Buffer, line);
        return isLine;
    }

}
