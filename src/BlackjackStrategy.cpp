#include "BlackjackStrategy.h"

#include "evol/Rng.h"

#include <iostream>

namespace blackjack{

Percentage::Percentage(int val)
: perc_(val / 100.0)
{}

void Percentage::crossover(Percentage const& other)
{
    perc_ += other.perc_;
    perc_ /= 2.0;
}

void Percentage::mutate()
{
    static thread_local evol::Rng rng;
    int randomStep = rng.fetchUniform(-2, 2, 1).top();
    perc_ += randomStep / 100.0;
    if(perc_ < 0)
        perc_ = 0;
    if(perc_ > 1)
        perc_ = 1;
}

std::string Percentage::toString() const
{
    return std::to_string(perc_*100) + "%";
}

bool Percentage::doIt(int threshold) const
{
    int percentage = int(perc_*100);
    return percentage >= threshold;
}

std::string BlackjackStrategy::toString() const
{
    std::string ret;
    ret += "Drawing Strategy:\n";
    for(const auto& [situation, percentage] : drawingPercentages)
    {
        const auto& [points, dealerRank] = situation;
        ret += points.toString() + ";";
        ret += dealerRank.toString() + ";";
        ret += percentage.toString() + ";";
        ret += "\n";
    }
    ret += "\n\n\n";
    ret += "Double Down Strategy:\n";
    for(const auto& [situation, percentage] : doubleDownPercentages)
    {
        const auto& [points, dealerRank] = situation;
        ret += points.toString() + ";";
        ret += dealerRank.toString() + ";";
        ret += percentage.toString() + ";";
        ret += "\n";
    }
    ret += "\n\n\n";
    ret += "Split Strategy:\n";
    for(const auto& [situation, percentage] : splitPercentages)
    {
        const auto& [playerRank, dealerRank] = situation;
        ret += playerRank.toString() + ";";
        ret += dealerRank.toString() + ";";
        ret += percentage.toString() + ";";
        ret += "\n";
    }
    return ret;
}

std::string BlackjackStrategy::toStringMat() const
{
    std::string ret;
    // drawing mat
    ret += "Drawing Strategy:\n";
    Points firstPoints;
    ret += ";";
    for(const auto& rank : BlackjackRank::createAll())
        ret += rank.toString() + ";";
    for(const auto& [situation, percentage] : drawingPercentages)
    {
        const auto& [points, dealerRank] = situation;
        if(points != firstPoints)
        {
            ret += "\n" + points.toString() + ';';
            firstPoints = points;
        }
        ret += percentage.toString() + ";";
    }

    // double down mat
    ret += "\nDouble Down Strategy:\n";
    firstPoints = {};
    ret += ";";
    for(const auto& rank : BlackjackRank::createAll())
        ret += rank.toString() + ";";
    for(const auto& [situation, percentage] : doubleDownPercentages)
    {
        const auto& [points, dealerRank] = situation;
        if(points != firstPoints)
        {
            ret += "\n" + points.toString() + ';';
            firstPoints = points;
        }
        ret += percentage.toString() + ";";
    }

    // split mat
    ret += "\nSplitting Strategy:\n";
    BlackjackRank firstRank = {};
    ret += ";";
    for(const auto& rank : BlackjackRank::createAll())
        ret += rank.toString() + ";";
    for(const auto& [situation, percentage] : splitPercentages)
    {
        const auto& [handRank, dealerRank] = situation;
        if(handRank != firstRank)
        {
            ret += "\n" + handRank.toString() + ';';
            firstRank = handRank;
        }
        ret += percentage.toString() + ";";
    }
    return ret;
}


BlackjackStrategy BlackjackStrategy::createTest(Percentage const& draw, Percentage const& doubleDown, Percentage const& split)
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

}