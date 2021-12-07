#include "Deck52.h"

#include <stdexcept>

namespace blackjack{

Card52 InfiniteDeck::dealCard(evol::Rng const& rng)
{
    int randomNumber = rng.fetchUniform(0, 51, 1).top();
    return Card52(randomNumber);
}

DeterministicDeck::DeterministicDeck(std::vector<Card52> const& cards)
: deck_(cards)
{}

Card52 DeterministicDeck::dealCard([[maybe_unused]] evol::Rng const& rng)
{
    if(deck_.empty())
        throw std::runtime_error("Empty deterministic deck.");
    Card52 ret = deck_[0];
    deck_.erase(deck_.begin());
    return ret;
}

std::vector<Card52> DeterministicDeck::deal(size_t N, evol::Rng const& rng)
{
    std::vector<Card52> ret;
    for(size_t i = 0; i < N; ++i)
        ret.push_back(dealCard(rng));
    return ret;
}

}