#pragma once

#include "BlackjackStrategy.h"

#include <optional>

namespace blackjack{

struct BlackjackGameSituation{
    std::optional<HandSituation> handSituation;
    bool isDraw = false;
    std::optional<SplitSituation> splitSituation;
    BlackjackStrategy strat;
    int nbGenerations = 100;
    int logLevel = 1;
};    

Percentage optimizeSitutation(BlackjackGameSituation const& situation);

BlackjackStrategy optimizeBlackjack(int cardCount = 0);

}