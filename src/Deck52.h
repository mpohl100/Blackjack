#pragma once

#include "BlackjackAnalysis.h"
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

namespace conceptify{

class CountedDeck{
public:
    CountedDeck(int count);
    CountedDeck() = default;
    CountedDeck(const CountedDeck&) = default;
    CountedDeck& operator=(const CountedDeck&) = default;
    CountedDeck(CountedDeck&&) = default;
    CountedDeck& operator=(CountedDeck&&) = default;
    Card52 dealCard(evol::Rng const& rng) override;
    int count() const;

    int getCount() const;
    int getNumberCards() const;
    Card52 getCard(const evol::Rng& rng);
private:
    int _count = 0;
    std::vector<Card52> _deck;
};

}

}