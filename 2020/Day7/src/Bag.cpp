#include "Bag.h"
#include <Util/String.h>
#include <algorithm>
//
// expecting a string which contains some adjective and specific colour with an underscore between them
// like 'muted_yellow'
//
Bag::Bag(std::string bagStr)
{
    
    m_Key = bagStr;
}

//
// adds a bag to the parent list of this bag (bags that can contain this one)
//
void Bag::AddParent(Bag* bag)
{
    m_Parents.push_back({ bag, 1 });
}

//
// adds a bag to the children list of this bag (bags that this bag can contain)
// with the given quantity
//
void Bag::AddChild(Bag* bag, int quant)
{
    m_Children.push_back({ bag, quant });
}

//
// gets a list of bags that can eventually contain this bag
//
void Bag::GetAllParentsRecursive(std::vector<Bag*> &container)
{
    for (BagQuant bag: m_Parents)
    {

        if(std::find(container.begin(), container.end(), bag.bag) == container.end())
            container.push_back(bag.bag);

        bag.bag->GetAllParentsRecursive(container);

    }

    return;
}

//
// Similar to the get parents function, this gets the number of children that must
// be contained in the bag (totaling their quantities too, as they are in the rules)
//
void Bag::GetAllChildrenRecursive(int& container)
{
    for (BagQuant bag : m_Children)
    {
        // need to do this multiple times if there have to be
        // multiple bags
        for(int i = 0; i < bag.quant; i++)
            bag.bag->GetAllChildrenRecursive(container);

        container += bag.quant;
    }

    return;
}

//
// bags are equal if they have the same key
//
bool Bag::operator==(Bag& other) const
{
    return this->m_Key == other.m_Key;
}
