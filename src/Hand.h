#pragma once

#include "Card52.h"

#include "evol/Rng.h"

#include <vector>

namespace blackjack{

struct BlackjackHand{
    std::vector<Card52> cards;
    static BlackjackHand fromString(std::string const& str);
    void addCard(Card52 const& card);
};

struct PlayerHand : public BlackjackHand{

};

struct DealerHand : public BlackjackHand{
    template<class Deck>
    void play( [[maybe_unused]] Deck const& deck, [[maybe_unused]] evol::Rng const& rng)
    {
        //size_t drawUntil = 17;
    }
};

}

