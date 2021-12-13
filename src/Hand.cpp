#include "Hand.h"
#include "BlackjackHand.h"

#include <range/v3/all.hpp>
#include <ranges>
#include <string>
#include <stdexcept>

namespace blackjack{

void BlackjackHand::addCard(Card52 const& card)
{
    cards.push_back(card);
}

BlackjackHand BlackjackHand::fromString(std::string const& str)
{
    auto cards = toCards(str);
    BlackjackHand hand;
    hand.cards = cards;
    return hand;
}

BlackjackHand::BlackjackHand(std::vector<Card52> const& cards)
: cards(cards)
{
    if(cards.size() != 2)
        throw std::runtime_error("Blackjack hand constructed without two cards.");
}

bool PlayerHand::isPair() const
{
    if(cards.size() != 2)
        return false;
    return cards[0].rank() == cards[1].rank();
}

BlackjackRank DealerHand::openCard() const
{
    return BlackjackRank(cards[0].rank());
}

}