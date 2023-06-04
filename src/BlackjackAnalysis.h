#pragma once

#include "BlackjackConcepts.h"
#include "BlackjackSituation.h"
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

bool optimizeSitutation(BlackjackGameSituation const& situation);

BlackjackStrategy optimizeBlackjack(int cardCount = 0);

namespace conceptify{

template<class BlackjackStrategyType, DeckConcept Deck>
requires BlackjackStrategyConcept<BlackjackStrategyType, Deck>
struct BlackjackGameSituation{
    std::optional<HandSituation> handSituation;
    bool isDraw = false;
    std::optional<SplitSituation> splitSituation;
    BlackjackStrategy strat;
    int nbGenerations = 100;
    int logLevel = 1;
};    

template<class BlackjackStrategyType, DeckConcept Deck>
requires BlackjackStrategyConcept<BlackjackStrategyType, Deck>
bool optimizeSitutation(BlackjackGameSituation<BlackjackStrategyType, Deck> const& situation)
{
    BlackjackChallenge::Type type = situation.splitSituation 
    ? BlackjackChallenge::Type::Split : situation.isDraw 
    ? BlackjackChallenge::Type::Draw : BlackjackChallenge::Type::DoubleDown;
    BlackjackChallenge<BlackjackStrategyType, Deck> challenge(type, getDealerRank(type, situation), getPlayerHand(type, situation), 
        situation.strat, std::make_unique<Deck>(deck) );
    // use absolute answers as a first test wether the expected results are met
    bool dont = false;
    bool doIt = true;
    double scoreDont = challenge.score(dont);
    double scoreDoIt = challenge.score(doIt);
    return scoreDoIt > scoreDont ? doIt : dont;
}

template<class BlackjackStrategyType>
requires BlackjackStrategyConcept<BlackjackStrategyType, CountedDeck>
BlackjackStrategyType optimizeBlackjack(int cardCount)
{
    BlackjackStrategyType<CountedDeck> result;
    CountedDeck deck(cardCount);
    // first optimize drawing
    for(size_t i = 21; i >= 2; i--)
    {
        auto blackjackRanks = BlackjackRank::createAll();
        for(BlackjackRank dealerRank : blackjackRanks)
        {
            BlackjackGameSituation situation;
            situation.isDraw = true;
            situation.strat = result; // all dependent game situations should be in the map
            HandSituation handSituation;
            handSituation.situation = Points(i, i);
            handSituation.dealerCard = dealerRank;
            situation.handSituation = std::make_optional<HandSituation>(handSituation);
            result.addDraw(handSituation, optimizeSitutation(situation, deck));
            HandSituation handSituationUpper;
            handSituationUpper.situation = Points(i, i+10);
            handSituationUpper.dealerCard = dealerRank;
            situation.handSituation = std::make_optional<HandSituation>(handSituationUpper);
            result.addDraw(handSituationUpper, optimizeSitutation(situation, deck));
        }
    }
    // then optimize double down
    for(size_t i = 21; i >= 2; i--)
    {
        auto blackjackRanks = BlackjackRank::createAll();
        for(BlackjackRank dealerRank : blackjackRanks)
        {
            BlackjackGameSituation situation;
            situation.isDraw = false;
            situation.strat = result; // all dependent game situations should be in the map
            HandSituation handSituation;
            handSituation.situation = Points(i, i);
            handSituation.dealerCard = dealerRank;
            situation.handSituation = std::make_optional<HandSituation>(handSituation);
            result.addDoubleDown(handSituation, optimizeSitutation(situation, deck));
            HandSituation handSituationUpper;
            handSituationUpper.situation = Points(i, i+10);
            handSituationUpper.dealerCard = dealerRank;
            situation.handSituation = std::make_optional<HandSituation>(handSituationUpper);
            result.addDoubleDown(handSituationUpper, optimizeSitutation(situation, deck));
        }
    }
    // then optimize split
    auto blackjackRanks = BlackjackRank::createAll();
    for(BlackjackRank splitRank : blackjackRanks)
    {
        for(BlackjackRank dealerRank : blackjackRanks)
        {
            BlackjackGameSituation situation;
            situation.isDraw = false;
            situation.strat = result; // all dependent game situations should be in the map
            SplitSituation splitSituation;
            splitSituation.situation = splitRank;
            splitSituation.dealerCard = dealerRank;
            situation.splitSituation = std::make_optional<SplitSituation>(splitSituation);
            result.addSplit(splitSituation, optimizeSitutation(situation, deck));
        }
    }
    return result;
}

}

}