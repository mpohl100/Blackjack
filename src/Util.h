#pragma once

#include "BlackjackPoints.h"
#include "BlackjackStrategy.h"
#include "Card52.h"
#include "Hand.h"
#include "UtilInternal.h"

#include "evol/Rng.h"

#include <stdexcept>
#include <vector>


namespace blackjack{

enum class PlayMode{
    All,
    DoubleDown,
    Draw,
};

template<class Deck>
// returns the payout
double playBlackjackHand(
    double playerBet, PlayerHand playerHand, DealerHand dealerHand, 
    Deck const& deck, BlackjackStrategy const& playerStrategy, evol::Rng const& rng, PlayMode playMode)
{
    // as a first version we play without double down and without split
    // play dealer hand at the beginning so that recursive versions for splitting use the same dealer outcome
    int dealerResult = dealerHand.play(deck, rng);

    // add code for splitting here
    if(playMode == PlayMode::All and playerHand.isPair()) // splitting hands is allowed
    {
        Rank52 rank = playerHand.cards[0].rank();
        auto it = playerStrategy.splitPercentages.find(rank);
        if(it == playerStrategy.splitPercentages.end())
            throw std::runtime_error("Split strategy not found for rank " + to_string(rank));
        bool doSplit = it->second.doIt(rng.fetchUniform(0, 100, 1).top());
        if(doSplit)
        {
            PlayerHand first;
            first.addCard(playerHand.cards[0]);
            first.addCard(deck.dealCard(rng));
            PlayerHand second;
            second.addCard(playerHand.cards[1]);
            second.addCard(deck.dealCard(rng));
            double overallResult = 0;
            overallResult += playBlackjackHand(playerBet, first, dealerHand, deck, playerStrategy, rng, playMode);
            overallResult += playBlackjackHand(playerBet, second, dealerHand, deck, playerStrategy, rng, playMode);
            return overallResult;
        }
    }

    Points playerPoints = {};
    while(true)
    {
        playerPoints = evaluateBlackjackHand(playerHand);
        auto it = playerStrategy.drawingPercentages.find(playerPoints);
        if(it == playerStrategy.drawingPercentages.end())
            throw std::runtime_error("Could not find playerPoints in BlackjackStrategy.drawingPercentages");
        const Percentage& percentage = it->second;
        int randomNumber = rng.fetchUniform(0, 100, 1).top(); 
        if( not percentage.doIt(randomNumber))
            break;
        playerHand.addCard(deck.dealCard(rng));
    }

    // deduce player result
    int playerResult = 0;
    if(playerPoints.upper <= 21)
        playerResult = playerPoints.upper;
    else
        playerResult = playerPoints.lower;

    // compare player and dealer hands
    if(playerResult > 21)
        return -playerBet;
    if(playerResult == 21 and playerHand.cards.size() == 2)
        return 2.5 * playerBet;
    if(dealerResult == -1)
        return playerBet;
    if(playerResult > dealerResult)
        return playerBet;
    return -playerBet;
}

}