#pragma once

#include "Card52.h"

#include <vector>

namespace blackjack{

struct BlackjackHand{
    std::vector<Card52> cards;
    static BlackjackHand fromString(std::string const& str);
};

}

