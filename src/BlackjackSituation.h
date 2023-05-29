#include "BlackjackPoints.h"
#include "Card52.h"

namespace blackjack{
    
template<class T>
struct BlackjackSituation{
    T situation;
    BlackjackRank dealerCard;
    
    BlackjackSituation(T const& sit, BlackjackRank dealerCard)
    : situation(sit)
    , dealerCard(dealerCard)
    {}

    BlackjackSituation() = default;
    BlackjackSituation(BlackjackSituation const&) = default;
    BlackjackSituation& operator=(BlackjackSituation const&) = default;
    BlackjackSituation(BlackjackSituation&&) = default;
    BlackjackSituation& operator=(BlackjackSituation&&) = default;

    friend constexpr auto operator<=>(BlackjackSituation const& l, BlackjackSituation const& r) = default;
    static std::vector<BlackjackSituation> createAll()
    {
        auto allSits = T::createAll();
        auto dealerCards = BlackjackRank::createAll();
        std::vector<BlackjackSituation> ret;
        for(const auto& sit : allSits)
            for(const auto& dealerCard : dealerCards)
                ret.push_back({sit, dealerCard});
        return ret;
    }
};

using HandSituation = BlackjackSituation<Points>;
using SplitSituation = BlackjackSituation<BlackjackRank>;
}