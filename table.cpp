#include "table.h"

Table::Table(int minimumBet, int maximumBet, int rounds)
    : minimumBet_{minimumBet}, maximumBet_{maximumBet}, rounds_{rounds}, runningCount_{0}, trueCount_{0}, players_{std::vector<Player>{}}

{
    players_.push_back(Player());
    initShoe();
    initDeal();
}
Table::Table()
    : Table::Table(10, 500, 100)
{
}
Hand::Hand() : cards_{std::vector<std::string>{}}, soft_{0} {}
Dealer::Dealer() : curHand_{Hand()} {}
Player::Player() : basicStrategy_{BasicStrategy()}, chips_{1000}, curBet_{0} {}

auto Table::initDeal() -> void
{
    for (auto i = 0; i < 2; i++)
    {
        for (auto it = players_.begin(); it != players_.end(); it++)
        {
            it->addCard(Table::deal());
        }
        dealer_.addCard(Table::deal());
    }
}
auto Table::deal() -> std::string
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0, shoe_.size());
    auto index = dist6(rng);
    auto card = shoe_.at(index);
    shoe_.erase(shoe_.begin() + index);
    return card;
}
auto Table::resolve() -> void
{
    for (auto it = players_.begin(); it != players_.end(); it++)
    {
        while (it->play(dealer_.shownCard()) != "Stand" && it->play(dealer_.shownCard()) != "Bust")
        {
            it->addCard(Table::deal());
        }
    }
    while (dealer_.play() != "Stand" && dealer_.play() != "Bust")
    {
        dealer_.addCard(Table::deal());
    }
}