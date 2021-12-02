
#include "UtilInternal.h"
#include "Card52.h"
#include "Deck52.h"

namespace blackjack{

Points evaluateBlackjackHand( BlackjackHand const& hand)
{
    bool encounteredAce = false;
    int lower = 0;
    int upper = 0;
    for(const Card52& card : hand.cards)
    {
        lower += card.toBlackjackScore();
        upper += card.toBlackjackScore();
        if(not encounteredAce and card.rank() == Rank52::Ace)
        {
            upper += 10;
            encounteredAce = true;
        }
    }
    return {lower, upper};
}

}