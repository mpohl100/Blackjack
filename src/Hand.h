#pragma once

#include "Card52.h"

#include "BlackjackConcepts.h"
#include "BlackjackHand.h"
#include "UtilInternal.h"

#include "evol/Rng.h"

#include <vector>

namespace blackjack{

struct PlayerHand : public BlackjackHand{
    using BlackjackHand::BlackjackHand;
    bool isPair() const;
};

struct DealerHand : public BlackjackHand{
    using BlackjackHand::BlackjackHand;
    template<class Deck>
    int play(Deck& deck, evol::Rng const& rng)
    {
        int drawUntil = 17;
        int result = 0;
        while(true)
        {
            Points points = evaluateBlackjackHand(*this);
            if(points.upper() >= drawUntil and points.upper() <= 21)
            {
                result = points.upper(); 
                break;
            }

            if(points.lower() >= drawUntil)
            {
                result = points.lower();
                break;
            }
            Card52 card;
            if constexpr(DeckConcept<Deck>){
                card = deck.getCard(rng);
            }
            else{
                card = deck.dealCard(rng);
            }
            addCard(card);
        }
        if(result > 21)
            return -1;
        return result;
    }
    BlackjackRank openCard() const;
};

}

