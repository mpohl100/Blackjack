#pragma once

#include "Card52.h"
#include "Hand.h"

#include <vector>

namespace blackjack{

struct Points{
    int lower = 0;
    int upper = 0;
    friend constexpr auto operator<=>(Points const& l, Points const& r) = default;
};

Points evaluateBlackjackHand( BlackjackHand const& hand);

}