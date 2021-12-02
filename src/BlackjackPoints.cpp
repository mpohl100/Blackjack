#include "BlackjackPoints.h"

namespace blackjack{

Points::Points(int lower, int upper)
: lower_(lower)
, upper_(upper)
{
    if(upper > 21)
        upper = lower;
}
int Points::lower() const
{
    return lower_;
}
int Points::upper() const
{
    return upper_;
}

std::string Points::toString() const
{
    return std::to_string(lower_) + "/" + std::to_string(upper_);
}

}