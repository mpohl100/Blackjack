#pragma once

#include "Card52.h"
#include "evol/Rng.h"

#include <vector>

namespace blackjack{

struct InfiniteDeck{
    Card52 dealCard(evol::Rng const& rng);
};

struct DeterministicDeck{
    DeterministicDeck(std::vector<Card52> const& cards);
    Card52 dealCard(evol::Rng const& rng);
    std::vector<Card52> deal(size_t N,evol::Rng const& rng);
private:
    std::vector<Card52> deck_;
};

}