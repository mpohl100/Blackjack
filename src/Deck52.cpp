#include "Deck52.h"

namespace blackjack{

Card52 InfiniteDeck::dealCard(evol::Rng const& rng) const
{
    int randomNumber = rng.fetchUniform(0, 51, 1).top();
    return Card52(randomNumber);
}

}