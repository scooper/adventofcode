#include "Group.h"
#include <Util/String.h>


Group::Group(std::string groupString)
{
    m_Members = 0;
    std::vector<std::string> memberStrings = AdventCommon::String::Split(groupString, "\n");

    for (std::string member : memberStrings)
    {
        m_Members++;
        for (auto it = member.begin(); it != member.end(); it++)
        {
            if (m_QuestionsAnswered.find(*it) == m_QuestionsAnswered.end())
                m_QuestionsAnswered[*it] = 1;
            else
                m_QuestionsAnswered[*it]++;
        }
    }
}

int Group::GetNumQuestionsAllAnsweredYes()
{

    int numWhereAllAnsweredYes = 0;

    for (const auto& [key, value] : m_QuestionsAnswered)
    {
        if (value == m_Members)
            numWhereAllAnsweredYes++;
    }

    return numWhereAllAnsweredYes;
}
