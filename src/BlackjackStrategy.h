#pragma once

#include "BlackjackConcepts.h"
#include "BlackjackPoints.h"
#include "BlackjackSituation.h"
#include "Deck52.h"

#include <map>
#include <stdexcept>

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


namespace conceptify{

class BlackjackStrategyMap{
public:
    template<DeckConcept Deck>  
    bool getDraw(const HandSituation& handSituation, [[maybe_unused]] const Deck& deck) const
    {
        const auto it = _draw.find(handSituation);
        if(it == _draw.cend()){
            throw std::runtime_error("Did not find hand situation " + handSituation.toString() + " in BlackjackStrategyMap::getDraw");
        }
        return it->second;
    };

    template<DeckConcept Deck>  
    bool getDoubleDown(const HandSituation& handSituation, [[maybe_unused]] const Deck& deck) const
    {
        const auto it = _doubleDown.find(handSituation);
        if(it == _doubleDown.cend()){
            throw std::runtime_error("Did not find hand situation " + handSituation.toString() + " in BlackjackStrategyMap::getDoubleDown");
        }
        return it->second;
    };

    template<DeckConcept Deck>  
    bool getSplit(const SplitSituation& splitSituation, [[maybe_unused]] const Deck& deck) const
    {
        const auto it = _split.find(splitSituation);
        if(it == _split.cend()){
            throw std::runtime_error("Did not find hand situation " + splitSituation.toString() + " in BlackjackStrategyMap::getSplit");
        }
        return it->second;
    };

    void addDraw(HandSituation handSituation, bool doIt);
    void addDoubleDown(HandSituation handSituation, bool doIt);
    void addSplit(SplitSituation splitSituation, bool doIt);
private:
    std::map<HandSituation, bool> _draw;
    std::map<HandSituation, bool> _doubleDown;
    std::map<SplitSituation, bool> _split;
};
}
}

