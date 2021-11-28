#include "BlackjackStrategy.h"

namespace blackjack{

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

}