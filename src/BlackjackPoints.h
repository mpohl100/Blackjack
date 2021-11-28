#pragma once

#include <compare>

namespace blackjack{

struct Points{
    int lower = 0;
    int upper = 0;
    friend constexpr auto operator<=>(Points const& l, Points const& r) = default;
};

}