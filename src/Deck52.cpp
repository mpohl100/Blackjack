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

CountedDeck::CountedDeck(int count)
    : count_(count)
{
    for(size_t i = 0; i < 52; ++i)
        deck_.emplace_back(i);
    if(count_ > 0)
    {
        int cnt = count_;
        std::erase_if(deck_,
        [&cnt](const Card52& card) mutable {
            if(cnt > 0 and BlackjackRank(card.rank()) == BlackjackRank(Ten))
            {
                cnt--;
                return true;
            }
            return false;        
        });
    }
    else if(count_ < 0)
    {
        int cnt = -count_;
        std::erase_if(deck_,
        [&cnt](const Card52& card) mutable {
            auto blackjackRank = BlackjackRank(card.rank());
            if(cnt > 0 and blackjackRank >= BlackjackRank(Deuce) and blackjackRank <= BlackjackRank(Six))
            {
                cnt--;
                return true;
            }
            return false;        
        });
    }
}

Card52 CountedDeck::dealCard(evol::Rng const& rng)
{
    int randomNumber = rng.fetchUniform(0, int(deck_.size())-1, 1).top();
    return deck_[randomNumber];
}

int CountedDeck::count() const
{
    return count_;
}

namespace conceptify{

CountedDeck::CountedDeck(int count)
: _count(count)
, _deck()
{
    for(size_t i = 0; i < 52; ++i)
        _deck.emplace_back(i);
    if(_count > 0)
    {
        int cnt = _count;
        std::erase_if(_deck,
        [&cnt](const Card52& card) mutable {
            if(cnt > 0 and BlackjackRank(card.rank()) == BlackjackRank(Ten))
            {
                cnt--;
                return true;
            }
            return false;        
        });
    }
    else if(_count < 0)
    {
        int cnt = -_count;
        std::erase_if(_deck,
        [&cnt](const Card52& card) mutable {
            auto blackjackRank = BlackjackRank(card.rank());
            if(cnt > 0 and blackjackRank >= BlackjackRank(Deuce) and blackjackRank <= BlackjackRank(Six))
            {
                cnt--;
                return true;
            }
            return false;        
        });
    }
}

int CountedDeck::getCount() const
{
    return _count;
}

int CountedDeck::getNumberCards() const
{
    return static_cast<int>(_deck.size());
}

Card52 CountedDeck::getCard(const evol::Rng& rng)
{
    int randomNumber = rng.fetchUniform(0, int(_deck.size())-1, 1).top();
    return _deck[randomNumber];
}

}
}