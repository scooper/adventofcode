//
// Simple wrapper for loading files and processing them into different formats
//
#pragma once
#include <vector>
#include <string>
#include <sstream>

namespace AdventCommon
{

    class File
    {
    public:
        File(const char* filepath);
        ~File();

       bool NextLine(std::string &line);
       std::string AsStr() { return m_Buffer.str(); }

    private:
        std::stringstream m_Buffer;
    };

}