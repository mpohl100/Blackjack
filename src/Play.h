#pragma once

#include "BlackjackConcepts.h"
#include "Hand.h"
#include "Util.h"

#include "evol/Rng.h"

#include <vector>

namespace blackjack::conceptify{

template<class BlackjackStrategyType, DeckConcept Deck>
requires BlackjackStrategyConcept<BlackjackStrategyType, Deck>
double playBlackjack(int N, const BlackjackStrategyType& blackjackStrategy, Deck& deck)
{
    auto rng = evol::Rng{};
    double result = 0.0;
    for(int i = 0; i < N; ++i){
        auto playerHand = PlayerHand(std::vector<Card52>{deck.getCard(rng), deck.getCard(rng)});
        auto dealerHand = DealerHand(std::vector<Card52>{deck.getCard(rng), deck.getCard(rng)});
        result += playBlackjackHand(1.0, playerHand, dealerHand, deck, blackjackStrategy, rng, PlayMode::All);
    }
    return result;
}

}