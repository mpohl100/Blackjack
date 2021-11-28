#pragma once

#include "BlackjackPoints.h"
#include "BlackjackStrategy.h"
#include "Card52.h"
#include "Hand.h"

#include "evol/Rng.h"

#include <stdexcept>
#include <vector>


namespace blackjack{

Points evaluateBlackjackHand( BlackjackHand const& hand);

enum class PlayMode{
    All,
    DoubleDown,
    Draw,
};

template<class Deck>
// returns the payout
double playBlackjackHand(
    [[maybe_unused]] double playerBet, PlayerHand playerHand, DealerHand dealerHand, 
    Deck deck, BlackjackStrategy const& playerStrategy, evol::Rng const& rng)
{
    // as a first version we play without double down and without split
    Points playerPoints;
    while(true)
    {
        playerPoints = evaluateBlackjackHand(playerHand);
        auto it = playerStrategy.drawingPercentages.find(playerPoints);
        if(it == playerStrategy.drawingPercentages.end())
            throw std::runtime_error("Could not find playerPoints in BlackjackStrategy");
        const Percentage& percentage = it->second;
        int randomNumber = rng.fetchUniform(0, 100, 1).top(); 
        if( not percentage.doIt(randomNumber))
            break;
        playerHand.addCard(deck.dealCard(rng));
    }
    dealerHand.play(deck, rng);
    return 0;
}

}