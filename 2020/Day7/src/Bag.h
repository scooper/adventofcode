#pragma once
#include <vector>
#include <unordered_map>
#include <string>

struct BagQuant;

class Bag
{
public:
    Bag() { m_Key = ""; }
    Bag(std::string bagStr);

    void AddParent(Bag* bag);
    void AddChild(Bag* bag, int quant);

    std::string m_Key;
    
    // get a list of bags that can eventually contain this bag
    void GetAllParentsRecursive(std::vector<Bag*> &container);
    void GetAllChildrenRecursive(int &container);

    bool operator==(Bag& other) const;

private:
    std::vector<BagQuant> m_Children;
    std::vector<BagQuant> m_Parents;

};

struct BagQuant
{
    Bag* bag;
    int quant;
};