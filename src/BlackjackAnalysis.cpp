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
                break;
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
    // use absolute answers as a first test wether the expected results are met
    Percentage dont = Percentage(0);
    Percentage doIt = Percentage(100);
    double scoreDont = challenge.score(dont);
    double scoreDoIt = challenge.score(doIt);
    return scoreDoIt > scoreDont ? doIt : dont;
}

BlackjackStrategy optimizeBlackjack()
{
    BlackjackStrategy result;
    // first optimize drawing
    for(size_t i = 21; i >= 2; i--)
    {
        for(BlackjackRank dealerRank : BlackjackRank::createAll())
        {
            BlackjackGameSituation situation;
            situation.isDraw = true;
            situation.strat = result; // all dependent game situations should be in the map
            HandSituation handSituation;
            handSituation.situation = Points(i, i);
            handSituation.dealerCard = dealerRank;
            situation.handSituation = std::make_optional<HandSituation>(handSituation);
            result.drawingPercentages[handSituation] = optimizeSitutation(situation);
            HandSituation handSituationUpper;
            handSituationUpper.situation = Points(i, i+10);
            handSituationUpper.dealerCard = dealerRank;
            situation.handSituation = std::make_optional<HandSituation>(handSituationUpper);
            result.drawingPercentages[handSituation] = optimizeSitutation(situation);
        }
    }
    // then optimize double down
    for(size_t i = 21; i >= 2; i--)
    {
        for(BlackjackRank dealerRank : BlackjackRank::createAll())
        {
            BlackjackGameSituation situation;
            situation.isDraw = false;
            situation.strat = result; // all dependent game situations should be in the map
            HandSituation handSituation;
            handSituation.situation = Points(i, i);
            handSituation.dealerCard = dealerRank;
            situation.handSituation = std::make_optional<HandSituation>(handSituation);
            result.doubleDownPercentages[handSituation] = optimizeSitutation(situation);
            HandSituation handSituationUpper;
            handSituationUpper.situation = Points(i, i+10);
            handSituationUpper.dealerCard = dealerRank;
            situation.handSituation = std::make_optional<HandSituation>(handSituationUpper);
            result.doubleDownPercentages[handSituation] = optimizeSitutation(situation);
        }
    }
    // then optimize split
    for(BlackjackRank splitRank : BlackjackRank::createAll())
    {
        for(BlackjackRank dealerRank : BlackjackRank::createAll())
        {
            BlackjackGameSituation situation;
            situation.isDraw = false;
            situation.strat = result; // all dependent game situations should be in the map
            SplitSituation splitSituation;
            splitSituation.situation = splitRank;
            splitSituation.dealerCard = dealerRank;
            situation.splitSituation = std::make_optional<SplitSituation>(splitSituation);
            result.splitPercentages[splitSituation] = optimizeSitutation(situation);
        }
    }
    return result;
}

}