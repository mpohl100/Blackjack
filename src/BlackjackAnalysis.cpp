#include "BlackjackAnalysis.h"
#include "BlackjackChallenge.h"

#include "evol/Evolution.h"

#include <stdexcept>

namespace blackjack{

BlackjackRank getDealerRank(BlackjackChallenge::Type type, BlackjackGameSituation const& situation)
{
    if(type == BlackjackChallenge::Type::Split)
        return situation.splitSituation->dealerCard;
    return situation.handSituation->dealerCard;
}

PlayerHand getPlayerHand(BlackjackChallenge::Type type, BlackjackGameSituation const& situation)
{
    PlayerHand ret;
    if(type == BlackjackChallenge::Type::Split)
    {
        ret.addCard(situation.splitSituation->situation.getRepresentativeCard());
        ret.addCard(situation.splitSituation->situation.getRepresentativeCard());
    }
    else
    {
        int goalPoints = situation.handSituation->situation.lower();
        if(goalPoints != situation.handSituation->situation.upper())
        {
            ret.addCard(Card52(Ace, Hearts));
            goalPoints--;
        }
        while(goalPoints > 0)
        {
            if(goalPoints >= 10)
            {
                ret.addCard(Card52(King, Hearts));
                goalPoints -= 10;
            }
            else{
                switch(goalPoints){
                    case 1: ret.addCard(Card52(Ace, Spades)); break;
                    case 2: ret.addCard(Card52(Deuce, Spades)); break;
                    case 3: ret.addCard(Card52(Three, Spades)); break;
                    case 4: ret.addCard(Card52(Four, Spades)); break;
                    case 5: ret.addCard(Card52(Five, Spades)); break;
                    case 6: ret.addCard(Card52(Six, Spades)); break;
                    case 7: ret.addCard(Card52(Seven, Spades)); break;
                    case 8: ret.addCard(Card52(Eight, Spades)); break;
                    case 9: ret.addCard(Card52(Nine, Spades)); break;
                    default: throw std::runtime_error("Unexpected goal points in generation of player hand: " + std::to_string(goalPoints));
                }
            }
        }
    }
    return ret;
}

Percentage optimizeSitutation(BlackjackGameSituation const& situation)
{

    BlackjackChallenge::Type type = situation.splitSituation 
        ? BlackjackChallenge::Type::Split : situation.isDraw 
        ? BlackjackChallenge::Type::Draw : BlackjackChallenge::Type::DoubleDown;
    BlackjackChallenge challenge(type, getDealerRank(type, situation), getPlayerHand(type, situation), situation.strat );
    std::vector<Percentage> initialPopulation;
    for(size_t i = 0; i < 20; ++i)
        initialPopulation.push_back(Percentage(50));
    evol::EvolutionOptions evolOpts;
    evolOpts.num_generations = situation.nbGenerations;
    evolOpts.log_level = situation.logLevel;
    evolOpts.out = &std::cout;
    double result = 0;
    auto winning = evol::evolution(initialPopulation, challenge, result, evolOpts);
    return winning.front();
}

}