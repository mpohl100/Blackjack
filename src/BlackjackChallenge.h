#pragma once

#include "BlackjackStrategy.h"
#include "Hand.h"
#include "Util.h"

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
        BlackjackStrategy const& strat);
    BlackjackChallenge() = default;
    BlackjackChallenge(BlackjackChallenge const&) = default;
    BlackjackChallenge& operator=(BlackjackChallenge const&) = default;
    BlackjackChallenge(BlackjackChallenge&&) = default;
    BlackjackChallenge& operator=(BlackjackChallenge&&) = default;

    double score(Percentage const& perc) const;
private:
    PlayMode getPlayMode() const;

    Type type_;
    BlackjackRank dealerRank_;
    PlayerHand playerHand_;
    mutable BlackjackStrategy strat_;
};

}