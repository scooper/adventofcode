#pragma once
#include <vector>
#include <string>
#include <sstream>

namespace AdventCommon
{

    class FileLoader
    {
    public:
        FileLoader(const char* filepath);
        ~FileLoader();

       bool NextLine(std::string &line);

    private:
        std::stringstream m_Buffer;
    };

}