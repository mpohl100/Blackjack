
#include "Util.h"
#include "Deck52.h"

#include <clara.hpp>

#include <iostream>

using namespace blackjack;

int main(int argc, char** argv)
{
    using namespace clara;


    std::string name;
    bool help = false;
    auto cli = Opt(name, "name")["-n"]["--name"]("name to greet") | Help(help);
     

    auto result = cli.parse(Args(argc, argv));
    if (!result) {
        std::cerr << "Error in command line: " << result.errorMessage() << '\n';
        exit(1);
    }
    if (help) {
        std::cout << cli;
        exit(0);
    }

    PlayerHand playerHand;
    DealerHand dealerHand;
    InfiniteDeck deck;
    BlackjackStrategy strat;
    evol::Rng rng;
    double ret = playBlackjackHand(1, playerHand, dealerHand, deck, strat, rng);
    std::cout << ret << '\n';
    return 0;
}

