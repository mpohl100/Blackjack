#include <catch2/catch.hpp>

#include "Util.h"

using namespace blackjack;

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
}

}