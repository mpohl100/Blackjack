#pragma once

#include "BlackjackConcepts.h"
#include "BlackjackPoints.h"
#include "BlackjackSituation.h"
#include "Deck52.h"
#include <map>

namespace blackjack{
struct BlackjackStrategy {
    // for the drawingPercentages first all cases for one ace ist contained must be solved for
    // 20 points and all dealer open cards
    // 19 points and all dealer open cards
    // ...
    // after all aces are solved we can then solve for all non ace hands
    std::map<HandSituation, bool> drawingPercentages;

    // we can solve the double down percentages independently of the drawing percentages
    std::map<HandSituation, bool> doubleDownPercentages;

    // the split percentages can be solved after the first two percentages 
    // as it can be played optimally from there on
    std::map<SplitSituation, bool> splitPercentages;

    std::string toStringMat2() const;
    static BlackjackStrategy createTest(bool draw, bool doubleDown, bool split);
};

static_assert(BlackjackStrategyConcept<BlackjackStrategy, Deck>);

}

