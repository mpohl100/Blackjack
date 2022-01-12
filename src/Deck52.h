#pragma once

#include "Card52.h"
#include "evol/Rng.h"

#include <vector>

namespace blackjack{

struct Deck{
    virtual Card52 dealCard(evol::Rng const& rng) = 0; 
    virtual ~Deck() = default;
};

struct InfiniteDeck : public Deck{
    Card52 dealCard(evol::Rng const& rng) override;
};

struct DeterministicDeck : public Deck{
    DeterministicDeck(std::vector<Card52> const& cards);
    Card52 dealCard(evol::Rng const& rng) override;
    std::vector<Card52> deal(size_t N,evol::Rng const& rng);
private:
    std::vector<Card52> deck_;
};

class CountedDeck : public Deck{
public:
    CountedDeck(int count);
    Card52 dealCard(evol::Rng const& rng) override;
    int count() const;
private:
    int count_ = 0;
    std::vector<Card52> deck_;
};

}