#pragma once

#include "Card52.h"

#include <vector>
#include <string>


namespace blackjack{

struct BlackjackHand{
    std::vector<Card52> cards;

    BlackjackHand(std::vector<Card52> const& cards);
    BlackjackHand() = default;
    BlackjackHand(BlackjackHand const&) = default;
    BlackjackHand& operator=(BlackjackHand const&) = default;
    BlackjackHand(BlackjackHand&&) = default;
    BlackjackHand& operator=(BlackjackHand&&) = default;

    static BlackjackHand fromString(std::string const& str);
    void addCard(Card52 const& card);
};

};