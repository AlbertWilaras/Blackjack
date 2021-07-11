#ifndef BASICSTRATEGY_H
#define BASICSTRATEGY_H

#include <map>

class BasicStrategy
{
public:
    BasicStrategy();
    auto getMove(int total, int dealerCard, bool isSoft, bool isPair) -> std::string
    {
        if (isPair)
        {
            if (isSoft)
            { //Pair of Aces
                return "Split";
            }
            return pairStrategy_[std::make_pair(total, dealerCard)];
        }
        else if (isSoft)
        {
            return softStrategy_[std::make_pair(total, dealerCard)];
        }
        else
        {
            if (total < 8)
            {
                return "Hit";
            }
            else if (total > 17)
            {
                return "Stand";
            }
            else
            {
                return hardStrategy_[std::make_pair(total, dealerCard)];
            }
        }
    }

private:
    std::map<std::pair<int, int>, std::string> hardStrategy_;
    std::map<std::pair<int, int>, std::string> softStrategy_;
    std::map<std::pair<int, int>, std::string> pairStrategy_;
};

#endif