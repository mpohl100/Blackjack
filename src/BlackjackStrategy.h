#pragma once

#include "BlackjackPoints.h"
#include "Card52.h"
#include <map>

namespace blackjack{

class Percentage{
public:
    Percentage(int val);
    Percentage() = default;
    Percentage(Percentage const&) = default;
    Percentage& operator=(Percentage const&) = default;
    Percentage(Percentage&&) = default;
    Percentage& operator=(Percentage&&) = default;
    void crossover(Percentage const& other);
    void mutate();
    std::string toString() const;
    bool doIt(int threshold) const;
private:
    double perc_ = 0.5;
};

template<class T>
struct BlackjackSituation{
    T situation;
    BlackjackRank dealerCard;
    friend constexpr auto operator<=>(BlackjackSituation const& l, BlackjackSituation const& r) = default;
    static std::vector<BlackjackSituation> createAll()
    {
        auto allSits = T::createAll();
        auto dealerCards = BlackjackRank::createAll();
        std::vector<BlackjackSituation> ret;
        for(const auto& sit : allSits)
            for(const auto& dealerCard : dealerCards)
                ret.push_back({sit, dealerCard});
        return ret;
    }
};

using HandSituation = BlackjackSituation<Points>;
using SplitSituation = BlackjackSituation<BlackjackRank>;

struct BlackjackStrategy {
    // for the drawingPercentages first all cases for one ace ist contained must be solved for
    // 20 points and all dealer open cards
    // 19 points and all dealer open cards
    // ...
    // after all aces are solved we can then solve for all non ace hands
    std::map<HandSituation, Percentage> drawingPercentages;

    // we can solve the double down percentages independently of the drawing percentages
    std::map<HandSituation, Percentage> doubleDownPercentages;

    // the split percentages can be solved after the first two percentages 
    // as it can be played optimally from there on
    std::map<SplitSituation, Percentage> splitPercentages;

    static BlackjackStrategy createTest(Percentage const& draw, Percentage const& doubleDown, Percentage const& split);
};

}

