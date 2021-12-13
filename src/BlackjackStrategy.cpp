#include "BlackjackStrategy.h"

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
    // todo implement
}

bool Percentage::doIt(int threshold) const
{
    int percentage = int(perc_*100);
    return percentage >= threshold;
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