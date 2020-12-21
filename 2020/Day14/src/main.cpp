#include <Util/File.h>
#include <Util/String.h>
#include <iostream>
#include <vector>
#include <string>
#include <bitset>
#include <unordered_map>

struct Bit
{
    bool masked;
    bool val;
};

unsigned long long GetValueWithBitmask(std::vector<Bit>& bitmask, unsigned long long val);
void UpdateBitmask(std::vector<Bit>& bitmask, std::string bitmaskStr);

int main()
{
    AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day14/input.txt");
    //AdventCommon::File file("D:/Projects/adventofcode/2020/inputs/Day14/inputTest.txt");

    std::unordered_map<int, unsigned long long> mem;
    std::vector<Bit> bitmask;

    std::string line;
    while (file.NextLine(line))
    {
        std::vector<std::string> split = AdventCommon::String::Split(line, " ");

        if (split[0] == "mask")
        {
            UpdateBitmask(bitmask, split[2]);
        }
        else
        {
            int index = atoi(split[0].substr(split[0].find("[") + 1, split[0].find("]")).c_str());
            int val = atoi(split[2].c_str());
            mem[index] = GetValueWithBitmask(bitmask, val);
        }


        //std::cout << "mem[" << index << "] = " << val << std::endl;
        //std::cout << "write result = " << mem[index] << std::endl;
    }

    unsigned long long result = 0;
    for (const auto& [key, value] : mem)
    {
        result += value;
    }

    std::cout << "Sum of memory vals = " << result << std::endl;

    return 0;
}

unsigned long long GetValueWithBitmask(std::vector<Bit>& bitmask, unsigned long long val)
{
    // we may as well make this 64 bit even though we'll only edit a max of 36
    std::bitset<64> bitset(val);

    for (int i = 0; i < bitmask.size(); i++)
    {
        Bit bm = bitmask[i];
        if (bm.masked)
        {
            bitset[i] = bm.val;
        }
    }
    
    return bitset.to_ullong();
}

void UpdateBitmask(std::vector<Bit>& bitmask, std::string bitmaskStr)
{
    bitmask.clear();
    for (char c : bitmaskStr)
    {
        switch (c)
        {
        case 'X':
            bitmask.insert(bitmask.begin(), { false, false });
            break;
        case '1':
            bitmask.insert(bitmask.begin(), { true, true });
            break;
        case '0':
            bitmask.insert(bitmask.begin(), { true, false });
            break;
        default:
            break;
        }
    }
}