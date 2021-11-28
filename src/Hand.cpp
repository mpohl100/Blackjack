#include "Hand.h"

#include <range/v3/all.hpp>
#include <ranges>
#include <string>

namespace blackjack{

BlackjackHand BlackjackHand::fromString(std::string const& str)
{
    auto cards =  str | ranges::views::split(' ')
                      | ranges::views::transform([](auto &&rng) {
        return std::string(&*rng.begin(), std::ranges::distance(rng));
    });
    BlackjackHand hand;
    for(auto const& card : cards)
        hand.cards.push_back(Card52(card));
    return hand;
}

}