#include "BlackjackPoints.h"

#include <set>

namespace blackjack{

Points::Points(int lower, int upper)
: lower_(lower)
, upper_(upper)
{
    if(upper_ > 21)
        upper_ = lower_;
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

std::vector<Points> Points::createAll()
{
    std::set<Points> points;
    for(int i = 4; i <= 21; ++i)
    {
        points.insert({i, i});
        points.insert({i, i+10});
    }
    return {points.begin(), points.end()};
}

}