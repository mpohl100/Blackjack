#include "BlackjackStrategy.h"

#include "evol/Rng.h"

#include <iostream>

namespace blackjack{

std::string BlackjackStrategy::toStringMat2() const
{
    std::map<HandSituation, std::string> hardStrat;
    std::map<HandSituation, std::string> softStrat;
    for(const auto& [situation, doIt] : doubleDownPercentages)
    {
        const auto& [points, dealerRank] = situation;
        std::map<HandSituation, std::string>& target = points.upper() == points.lower() ? hardStrat : softStrat;
        if(doIt)
            target[situation] = "D";
        else if(drawingPercentages.at(situation))
            target[situation] = "H";
        else
            target[situation] = "S";
    }

    std::string ret = "Hard hands strategy:\n";
    Points firstPoints;
    ret += ";";
    for(const auto& rank : BlackjackRank::createAll())
        ret += rank.toString() + ";";
    for(const auto& [situation, action] : hardStrat)
    {
        const auto& [points, dealerRank] = situation;
        if(points != firstPoints)
        {
            ret += "\n" + points.toString() + ';';
            firstPoints = points;
        }
        ret += action + ";";
    }

    
    ret += "\nSoft hands strategy:\n";
    firstPoints = {};
    ret += ";";
    for(const auto& rank : BlackjackRank::createAll())
        ret += rank.toString() + ";";
    for(const auto& [situation, action] : softStrat)
    {
        const auto& [points, dealerRank] = situation;
        if(points != firstPoints)
        {
            ret += "\n" + points.toString() + ';';
            firstPoints = points;
        }
        ret += action + ";";
    }

    ret += "\nSplitting Strategy:\n";
    BlackjackRank firstRank = {};
    ret += ";";
    for(const auto& rank : BlackjackRank::createAll())
        ret += rank.toString() + ";";
    for(const auto& [situation, doIt] : splitPercentages)
    {
        const auto& [handRank, dealerRank] = situation;
        if(handRank != firstRank)
        {
            ret += "\n" + handRank.toString() + ';';
            firstRank = handRank;
        }
        ret += (doIt ? std::string("P") : std::string("-")) + ";";
    }
    return ret;
}


BlackjackStrategy BlackjackStrategy::createTest(bool draw, bool doubleDown, bool split)
{
    BlackjackStrategy ret;
    auto handSituations = HandSituation::createAll();
    for(const auto& handSituation : handSituations)
        ret.drawingPercentages[handSituation] = draw;    
    for(const auto& handSituation : handSituations)
        ret.doubleDownPercentages[handSituation] = doubleDown;
    auto splitSituations = SplitSituation::createAll();
    for(const auto& splitSituation : splitSituations)
        ret.splitPercentages[splitSituation] = split;
    return ret;
}

namespace conceptify{

void BlackjackStrategyMap::addDraw(HandSituation handSituation, bool doIt)
{
    _draw[handSituation] = doIt;
}

void BlackjackStrategyMap::addDoubleDown(HandSituation handSituation, bool doIt)
{
    _doubleDown[handSituation] = doIt;
}

void BlackjackStrategyMap::addSplit(SplitSituation splitSituation, bool doIt)
{
    _split[splitSituation] = doIt;
}

//static_assert(BlackjackStrategyConcept<BlackjackStrategyMap>);

}

}