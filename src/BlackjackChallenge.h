#pragma once

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

}