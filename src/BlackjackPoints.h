#pragma once

#include <compare>
#include <string>
#include <vector>

namespace blackjack{

struct Points{
    Points() = default;
    Points(Points const&) = default;
    Points& operator=(Points const&) = default;
    Points(Points&&) = default;
    Points& operator=(Points&&) = default;
    Points(int lower, int upper);
    int lower() const;
    int upper() const;
    friend constexpr auto operator<=>(Points const& l, Points const& r) = default;
    std::string toString() const;
    static std::vector<Points> createAll();
private:
    int lower_ = -10000;
    int upper_ = -10000;
};

}