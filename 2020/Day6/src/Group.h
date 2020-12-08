#pragma once

#include <string>
#include <unordered_map>

class Group
{
public:
    Group(std::string groupString);
    int GetMembers() { return m_Members; }
    int GetNumQuestionsAnsweredYes() { return m_QuestionsAnswered.size(); }
    int GetNumQuestionsAllAnsweredYes();

private:
    int m_Members;
    std::unordered_map<char, int> m_QuestionsAnswered;
};