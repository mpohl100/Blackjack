#include "BlackjackStrategy.h"

#include "evol/Rng.h"

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
    return percentage <= threshold;
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