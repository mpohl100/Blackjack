#include "Util.h"
#include "Hand.h"

namespace blackjack::conceptify{

double deducePlayerResult(double playerResult, double playerBet, const PlayerHand& playerHand, double dealerResult)
{
        // compare player and dealer hands
    if(playerResult > 21)
        return -playerBet;
    if(playerResult == 21 and playerHand.cards.size() == 2)
        return 1.5 * playerBet;
    if(dealerResult == -1)
        return playerBet;
    if(playerResult > dealerResult)
        return playerBet;
    if(playerResult == dealerResult)
        return 0;
    return -playerBet;
}

}