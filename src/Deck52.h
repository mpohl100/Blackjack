#pragma once

#include "Card52.h"
#include "evol/Rng.h"

namespace blackjack{

struct InfiniteDeck{
    Card52 dealCard(evol::Rng const& rng) const;
};

}