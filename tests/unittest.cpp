#include <catch2/catch.hpp>

#include "UtilInternal.h"
#include "Deck52.h"
#include "Hand.h"
#include "Util.h"

using namespace blackjack;

std::pair<DealerHand, int> dealDealerHand(std::string const& str)
{
    evol::Rng rng;
    DeterministicDeck deck(toCards(str));
    auto cards = deck.deal(2, rng);
    DealerHand dealerHand{cards};
    int result = dealerHand.play(deck, rng);
    return {dealerHand, result};
}

double playHand(std::string const& str, PlayMode playMode)
{
    evol::Rng rng;
    DeterministicDeck deck(toCards(str));
    auto cards = deck.deal(2, rng);
    DealerHand dealerHand{cards};    
    cards = deck.deal(2, rng);
    PlayerHand playerHand{cards};
    BlackjackStrategy strat = BlackjackStrategy::createTest(true, false, false);
    return playBlackjackHand(1, playerHand, dealerHand, deck, strat, rng, playMode);
}

namespace {



TEST_CASE("Blackjack", "[blackjack]"){
    SECTION("Points Deduction One Card"){
        auto hand = BlackjackHand::fromString("Ah");
        Points points = evaluateBlackjackHand(hand);
        CHECK(points == Points{1, 11});
        hand = BlackjackHand::fromString("2h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{2, 2});
        hand = BlackjackHand::fromString("3h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{3, 3});
        hand = BlackjackHand::fromString("4h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{4, 4});
        hand = BlackjackHand::fromString("5h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{5, 5});
        hand = BlackjackHand::fromString("6h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{6, 6});
        hand = BlackjackHand::fromString("7h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{7, 7});
        hand = BlackjackHand::fromString("8h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{8, 8});        
        hand = BlackjackHand::fromString("9h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{9, 9});       
        hand = BlackjackHand::fromString("Th");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{10, 10});       
        hand = BlackjackHand::fromString("Jh");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{10, 10});       
        hand = BlackjackHand::fromString("Qh");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{10, 10});       
        hand = BlackjackHand::fromString("Kh");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{10, 10});
    }
    SECTION("Points Deduction 2 Cards"){
        auto hand = BlackjackHand::fromString("As Ah");
        Points points = evaluateBlackjackHand(hand);
        CHECK(points == Points{2, 12});
        hand = BlackjackHand::fromString("As 2h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{3, 13});
        hand = BlackjackHand::fromString("As 3h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{4, 14});
        hand = BlackjackHand::fromString("As 4h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{5, 15});
        hand = BlackjackHand::fromString("As 5h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{6, 16});
        hand = BlackjackHand::fromString("As 6h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{7, 17});
        hand = BlackjackHand::fromString("As 7h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{8, 18});
        hand = BlackjackHand::fromString("As 8h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{9, 19});        
        hand = BlackjackHand::fromString("As 9h");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{10, 20});       
        hand = BlackjackHand::fromString("As Th");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{11, 21});       
        hand = BlackjackHand::fromString("As Jh");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{11, 21});       
        hand = BlackjackHand::fromString("As Qh");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{11, 21});       
        hand = BlackjackHand::fromString("As Kh");
        points = evaluateBlackjackHand(hand);
        CHECK(points == Points{11, 21});
    }
    SECTION("Deal Dealer Hand"){

        auto checkDealerHand = [&](std::string const& str, int expectedResult)
        {
            auto result = dealDealerHand(str);
            CHECK(result.first.cards == toCards(str));
            CHECK(result.second == expectedResult);
        };
        // straight forward results
        checkDealerHand("As Qs", 21);
        checkDealerHand("Ks Qs", 20);
        checkDealerHand("Ks 9s", 19);   
        checkDealerHand("Ks 8s", 18); 
        checkDealerHand("Ks 7s", 17);
        // three cards stay at 17
        checkDealerHand("Ks 6h Ad", 17);
        checkDealerHand("Ks 6h 2d", 18);
        checkDealerHand("Ks 6h 3d", 19);
        checkDealerHand("Ks 6h 4d", 20);
        checkDealerHand("Ks 6h 5d", 21);
        checkDealerHand("Ks 6h 6d", -1);
        // draw until 17 with ace
        checkDealerHand("Ad 5h As", 17);
        checkDealerHand("Ad 5h 2s", 18);
        checkDealerHand("Ad 5h 3s", 19);
        checkDealerHand("Ad 5h 4s", 20);
        checkDealerHand("Ad 5h 5s", 21);
        checkDealerHand("Ad 5h 6s Kd", -1);
    }
}

}