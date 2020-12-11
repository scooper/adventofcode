#pragma once
#include <vector>

namespace AdventCommon
{
    class Collections
    {
    public:
        //
        // returns a pair of objects that sum to the given object X (expects a sorted vector)
        // (only really useful for numbers but its okay to keep it generalised for this purpose)
        //
        template<class T>
        static std::vector<T> FindPairElementsThatSumToX(std::vector<T>& numbers, T x)
        {
            // go from the front of the sorted set and backwards from the end of the set, checking for a sum
            std::vector<T> desiredNums;
            // better to do this with iterators?
            // find the match
            for (int front = 0, back = numbers.size() - 1; front < back;)
            {
                T total = numbers[front] + numbers[back];
                if (total > x)
                {
                    back--;
                }
                else if (total < x)
                {
                    front++;
                }
                else
                {
                    // yay
                    desiredNums.push_back(numbers[front]);
                    desiredNums.push_back(numbers[back]);
                    break;
                }
            }

            return desiredNums;
        }

        //
        // Finds N contiguous elements (that are directly next to eachother in the collection) that sum to X
        // where N > min
        //
        template<class T>
        static std::vector<T> FindContiguousNElementsThatSumToX(std::vector<T>& numbers, T x, int minElements = 2)
        {
            for (typename std::vector<T>::const_iterator it = numbers.begin(); it != numbers.end(); it++)
            {
                std::vector<T> contiguousNums;
                int total = 0;

                for (typename std::vector<T>::const_iterator it2 = it; it2 != numbers.end(); it2++)
                {
                    total += *it2;
                    contiguousNums.push_back(*it2);

                    // we've already passed our target so try the next set
                    if (total > x)
                        break;

                    // difference between our start iterator and current iterator, and make it 1 indexed style
                    int iterations = (it2 - it) + 1;

                    // if we're at our total we return
                    // only if we have iterated to at least our minimum
                    // (default 2 since there is a chance our target just exists on its own in the collection)
                    if (total == x && iterations >= minElements)
                        return contiguousNums;
                }
            }
            return std::vector<T>();
        }
    };
}

