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
    Deck& deck, BlackjackStrategy const& playerStrategy, 
    evol::Rng const& rng, PlayMode playMode)
{
    // as a first version we play without double down and without split
    // play dealer hand at the beginning so that recursive versions for splitting use the same dealer outcome
    int dealerResult = dealerHand.play(deck, rng);

    // add code for splitting here
    if(playMode == PlayMode::All and playerHand.isPair()) // splitting hands is allowed
    {
        Rank52 rank = playerHand.cards[0].rank();
        auto it = playerStrategy.splitPercentages.find({rank, dealerHand.openCard()});
        if(it == playerStrategy.splitPercentages.end())
            throw std::runtime_error("Split strategy not found for rank " + to_string(rank) + "/" + to_string(dealerHand.openCard()));
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
    bool onlyDrawOnce = false;
    if(playMode == PlayMode::All or playMode == PlayMode::DoubleDown)
    {
        playerPoints = evaluateBlackjackHand(playerHand);
        auto it = playerStrategy.doubleDownPercentages.find({playerPoints, dealerHand.openCard()});
        if(it == playerStrategy.doubleDownPercentages.end())
        {
            throw std::runtime_error("Double down strategy not found " + playerPoints.toString() + "/" + to_string(dealerHand.openCard()));
        }
        int randomNumber = rng.fetchUniform(0, 100, 1).top(); 
        onlyDrawOnce = it->second.doIt(randomNumber);   
    }
    while(true)
    {
        playerPoints = evaluateBlackjackHand(playerHand);
        auto it = playerStrategy.drawingPercentages.find({playerPoints, dealerHand.openCard()});
        if(it == playerStrategy.drawingPercentages.end())
            throw std::runtime_error("Drawing strategy not found " + playerPoints.toString() + "/" + to_string(dealerHand.openCard()));
        const Percentage& percentage = it->second;
        if(not onlyDrawOnce)
        {
            int randomNumber = rng.fetchUniform(0, 100, 1).top(); 
            if( not percentage.doIt(randomNumber))
                break;
        }
        playerHand.addCard(deck.dealCard(rng));
        if(onlyDrawOnce)
            break;
    }

    // deduce player result
    int playerResult = playerPoints.upper();

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