#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <iostream>
#include <random>
#include "basicStrategy.h"
#include <cassert>

class Hand
{
public:
    Hand();
    auto getHandSize() -> int { cards_.size(); }
    auto getCardAt(int index) -> std::string { return cards_.at(index); }
    auto addCard(std::string const card) -> void
    {
        cards_.push_back(card);
    }
    auto getValue() -> int
    {
        auto total = 0;
        for (auto it = cards_.begin(); it != cards_.end(); it++)
        {
            //only "10" has more than 1 char
            if (it->size() > 1)
            {
                total += 10;
            }
            else if (isdigit(it->at(0)))
            {
                total += std::stoi(*it);
            }
            else if (*it == "A")
            {
                total += 11;
                soft_++;
            }
            else
            { //face cards
                total += 10;
            }
            while (total > 21 && soft_ > 0)
            {
                total -= 10;
                soft_--;
            }
        }
        return total;
    }
    auto isSoft() -> int { return soft_; }
    auto isPair() -> bool
    {
        if (cards_.size() == 2 && *(cards_.begin()) == *(cards_.begin() + 1))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    friend std::ostream &operator<<(std::ostream &os, const Hand &hand)
    {
        for (auto it = hand.cards_.begin(); it != hand.cards_.end(); it++)
        {
            os << *it << " ";
        }
        return os;
    }

private:
    std::vector<std::string> cards_;
    int soft_;
};

class Dealer
{
public:
    Dealer();
    auto addCard(std::string const card) -> void { curHand_.addCard(card); }
    auto shownCard() -> std::string
    {
        assert(curHand_.getHandSize() >= 2);
        return curHand_.getCardAt(1);
    }
    auto checkBlackjack() -> bool
    {
        if (curHand_.getValue() == 21 && curHand_.getHandSize() == 2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    auto play() -> std::string
    {
        //std::cout << "DEALER TOTAL: " << curHand_.getValue() << "\n";
        if (curHand_.getValue() < 17)
        {
            return "Hit";
        }
        else if (curHand_.getValue() > 21)
        {
            return "Bust";
        }
        else
        {
            return "Stand";
        }
    }
    friend std::ostream &operator<<(std::ostream &os, const Dealer &dealer)
    {
        os << dealer.curHand_;
        return os;
    }

private:
    Hand curHand_;
};

class Player
{
public:
    Player();
    Player(int chips_);
    auto play(std::string dealerCard) -> std::string
    {
        if (curHand_.getValue() > 21)
        {
            return "Bust";
        }
        auto dealerValue = 0;
        if (dealerCard.size() > 1)
        {
            dealerValue = 10;
        }
        else if (isdigit(dealerCard.at(0)))
        {
            dealerValue = std::stoi(dealerCard);
        }
        else if (dealerCard == "A")
        {
            dealerValue = 11;
        }
        else
        { //face cards
            dealerValue = 10;
        }
        auto isSoft = false;
        if (curHand_.isSoft() > 0)
        {
            isSoft = true;
        }
        return basicStrategy_.getMove(curHand_.getValue(), dealerValue, isSoft, curHand_.isPair());
    }
    //auto bet(int runningCount, int trueCount, int minimumBet);
    //auto win(int winnings);
    //auto split();
    auto addCard(std::string card) -> void { curHand_.addCard(card); }
    friend std::ostream &operator<<(std::ostream &os, const Player &player)
    {
        os << player.curHand_;
        return os;
    }

private:
    //std::vector<Hand> hands_;
    BasicStrategy basicStrategy_;
    Hand curHand_;
    int chips_;
    int curBet_;
    //int totalBet_;
};

class Table
{

public:
    Table(int minimumBet, int maximumBet, int rounds);
    Table();
    auto getMinimumBet() -> int { return minimumBet_; }
    auto getMaximumBet() -> int { return maximumBet_; }
    auto getRounds() -> int { return rounds_; }
    auto initDeal() -> void;
    auto deal() -> std::string;
    auto resolve() -> void;
    friend std::ostream &operator<<(std::ostream &os, const Table &table)
    {
        os << "Dealer Cards: " << table.dealer_ << "\n";
        for (auto i = 0; i < table.players_.size(); i++)
        {
            os << "Player " << i << " Cards: " << table.players_[i];
            if (i + 1 < table.players_.size())
            {
                os << "\n";
            }
        }

        return os;
    }

private:
    auto initShoe() -> void
    {
        auto possibleCards = std::vector<std::string>{"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

        for (auto it = possibleCards.begin(); it != possibleCards.end(); it++)
        {
            //Assumes 6 deck blackjack, hence 24 copies of each card in the shoe
            for (auto j = 0; j < 24; j++)
            {
                shoe_.push_back(*it);
            }
        };
    }
    std::vector<std::string> shoe_;
    Dealer dealer_;
    std::vector<Player> players_;
    const int minimumBet_;
    const int maximumBet_;
    const int rounds_;
    int runningCount_;
    int trueCount_;
};

#endif