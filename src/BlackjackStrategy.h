#pragma once

#include "BlackjackPoints.h"
#include "Card52.h"
#include <map>

namespace blackjack{

class Percentage{
public:
    void crossover(Percentage const& other);
    void mutate();
    bool doIt(int threshold) const;
private:
    double perc_ = 0.5;
};

struct BlackjackStrategy {
    // for the drawingPercentages first all cases for one ace ist contained must be solved for
    // 20 points and all dealer open cards
    // 19 points and all dealer open cards
    // ...
    // after all aces are solved we can then solve for all non ace hands
    std::map<Points, Percentage> drawingPercentages;

    // we can solve the double down percentages independently of the drawing percentages
    std::map<Points, Percentage> doubleDownPercentages;

    // the split percentages can be solved after the first two percentages 
    // as it can be played optimally from there on
    std::map<Rank52, Percentage> splitPercentages;
};

}

