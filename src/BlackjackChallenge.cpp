#include "BlackjackChallenge.h"
#include "UtilInternal.h" 
#include "Deck52.h"
#include "Util.h"

namespace blackjack{

BlackjackChallenge::BlackjackChallenge( Type type,
    BlackjackRank dealerCard, PlayerHand const& playerHand,
    BlackjackStrategy const& strat)
: type_(type)
, dealerRank_(dealerCard)
, playerHand_(playerHand)
, strat_(strat)
{}

double BlackjackChallenge::score(Percentage const& perc) const
{
    auto points = evaluateBlackjackHand(playerHand_);
    if(type_ == Type::Draw)
        strat_.drawingPercentages[{points, dealerRank_}] = perc;
    else if(type_ == Type::DoubleDown)
        strat_.doubleDownPercentages[{points, dealerRank_}] = perc;
    else if(type_ == Type::Split)
        strat_.splitPercentages[{BlackjackRank(playerHand_.cards[0].rank()), dealerRank_}] = perc;
    double result = 0;
    InfiniteDeck deck;
    evol::Rng rng;
    for(size_t i = 0; i < 1000; ++i)
    {
        DealerHand dealerHand;
        dealerHand.addCard(dealerRank_.getRepresentativeCard());
        dealerHand.addCard(deck.dealCard(rng));
        result += playBlackjackHand(1.0, playerHand_, dealerHand, deck, strat_, rng, getPlayMode());
    }
    return result;
}

PlayMode BlackjackChallenge::getPlayMode() const
{
    switch(type_){
        case Type::Draw: return PlayMode::Draw;
        case Type::DoubleDown: return PlayMode::DoubleDown;
        case Type::Split: return PlayMode::All;
    }
}

}