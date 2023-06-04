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

template<DeckConcept Deck>
int getClampedCount(const Deck& deck, int minCount, int maxCount)
{
    int nbCards = deck.getNbCards();
    int deckCount = deck.getCount();
    double ratio = static_cast<double>(deckCount) / nbCards;
    int count = static_cast<int>(ratio * 52.0);
    if(count > maxCount) {
        return maxCount;
    }
    else if(count < minCount) {
        return minCount;
    } else {
        return count;
    }
}

template<class BlackjackStrategyType, DeckConcept Deck>
requires BlackjackStrategyConcept<BlackjackStrategyType, Deck>
class CountedBlackjackStrategy{
public:
    bool getDraw(const HandSituation& handSituation, const Deck& deck) const
    {
        int count = getClampedCount(deck, _strats.begin()->first, _strats.rbegin()->first);
        const auto it = _strats.find(count);
        if(it == _strats.cend()){
            throw std::runtime_error("Strategy with count " + std::to_string(count) + " not found in CountedBlackjackStrategy");
        }
        return it->second.getDraw(handSituation, deck);
    };

    bool getDoubleDown(const HandSituation& handSituation, const Deck& deck) const
    {
        int count = getClampedCount(deck, _strats.begin()->first, _strats.rbegin()->first);
        const auto it = _strats.find(count);
        if(it == _strats.cend()){
            throw std::runtime_error("Strategy with count " + std::to_string(count) + " not found in CountedBlackjackStrategy");
        }
        return it->second.getDoubleDown(handSituation, deck);
    };
 
    bool getSplit(const SplitSituation& splitSituation, const Deck& deck) const
    {
        int count = getClampedCount(deck, _strats.begin()->first, _strats.rbegin()->first);
        const auto it = _strats.find(count);
        if(it == _strats.cend()){
            throw std::runtime_error("Strategy with count " + std::to_string(count) + " not found in CountedBlackjackStrategy");
        }
        return it->second.getSplit(splitSituation, deck);
    };

    void addDraw([[maybe_unused]] HandSituation handSituation, [[maybe_unused]] bool doIt){};
    void addDoubleDown([[maybe_unused]] HandSituation handSituation, [[maybe_unused]] bool doIt){};
    void addSplit([[maybe_unused]] SplitSituation splitSituation, [[maybe_unused]] bool doIt){};
    void addBlackjackStrategy(int count, const BlackjackStrategyType& strat)
    {
        _strats[count] = strat;
    }
private:
    std::map<int, BlackjackStrategyType> _strats;
};
}
}

