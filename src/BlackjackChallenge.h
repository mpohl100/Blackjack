#pragma once


#include "BlackjackConcepts.h"
#include "BlackjackStrategy.h"
#include "Hand.h"
#include "Util.h"
#include "Deck52.h"

#include <memory>

namespace blackjack{

class BlackjackChallenge{
public:
    enum class Type{
        Draw,
        DoubleDown,
        Split,
    };
    BlackjackChallenge(
        Type type,
        BlackjackRank dealerCard, PlayerHand const& playerHand,
        BlackjackStrategy const& strat, std::unique_ptr<Deck>  deck);
    BlackjackChallenge() = default;
    BlackjackChallenge(BlackjackChallenge&&) = default;
    BlackjackChallenge& operator=(BlackjackChallenge&&) = default;

    double score(bool doIt) const;
private:
    PlayMode getPlayMode() const;

    Type type_;
    BlackjackRank dealerRank_;
    PlayerHand playerHand_;
    mutable BlackjackStrategy strat_;
    std::unique_ptr<Deck> deck_;
};

namespace conceptify{

template<class BlackjackStrategyType, DeckConcept Deck>
requires BlackjackStrategyConcept<BlackjackStrategyType, Deck>
class BlackjackChallenge{
public:
    enum class Type{
        Draw,
        DoubleDown,
        Split,
    };
    BlackjackChallenge(
        Type type,
        BlackjackRank dealerCard, PlayerHand const& playerHand,
        BlackjackStrategyType const& strat, std::unique_ptr<Deck>  deck)
        : type_(type)
        , dealerRank_(dealerCard)
        , playerHand_(playerHand)
        , strat_(strat)
        , deck_(std::move(deck))
    {}
    BlackjackChallenge() = default;
    BlackjackChallenge(BlackjackChallenge&&) = default;
    BlackjackChallenge& operator=(BlackjackChallenge&&) = default;

    double score(bool doIt) const
    {
        auto points = evaluateBlackjackHand(playerHand_);
        if(type_ == Type::Draw)
            strat_.addDraw({points, dealerRank_}, doIt);
        else if(type_ == Type::DoubleDown)
            strat_.addDoubleDown({points, dealerRank_}, doIt);
        else if(type_ == Type::Split)
            strat_.addSplit({BlackjackRank(playerHand_.cards[0].rank()), dealerRank_}, doIt);
        double result = 0;
        evol::Rng rng;
        for(size_t i = 0; i < 2000; ++i)
        {
            DealerHand dealerHand;
            dealerHand.addCard(dealerRank_.getRepresentativeCard());
            dealerHand.addCard(deck_->getCard(rng));
            result += playBlackjackHand(1.0, playerHand_, dealerHand, *deck_, strat_, rng, getPlayMode());
        }
        return result;
    }
private:
    PlayMode getPlayMode() const
    {
        switch(type_){
            case Type::Draw: return PlayMode::Draw;
            case Type::DoubleDown: return PlayMode::DoubleDown;
            case Type::Split: return PlayMode::All;
        }
    }

    Type type_;
    BlackjackRank dealerRank_;
    PlayerHand playerHand_;
    mutable BlackjackStrategyType strat_;
    std::unique_ptr<Deck> deck_;
};
}

}