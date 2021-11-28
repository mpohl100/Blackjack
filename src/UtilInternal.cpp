
#include "UtilInternal.h"
#include "Card52.h"
#include "Deck52.h"

namespace blackjack{

Points evaluateBlackjackHand( BlackjackHand const& hand)
{
    Points ret;
    bool encounteredAce = false;
    for(const Card52& card : hand.cards)
    {
        ret.lower += card.toBlackjackScore();
        ret.upper += card.toBlackjackScore();
        if(not encounteredAce and card.rank() == Rank52::Ace)
        {
            ret.upper += 10;
            encounteredAce = true;
        }
    }
    return ret;
}

}