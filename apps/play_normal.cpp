
#include "BlackjackAnalysis.h"
#include "BlackjackStrategy.h"
#include "Play.h"
#include "Deck52.h"

#include <clara.hpp>

#include <iostream>

using namespace blackjack;

int main(int argc, char** argv)
{
    using namespace clara;


    bool help = false;
    int N = 1000000;
    auto cli = Opt(N, "number_hands")["-n"]["--number-hands"]("the number of hands to play after deducing the strategy") | Help(help);
     

    auto result = cli.parse(Args(argc, argv));
    if (!result) {
        std::cerr << "Error in command line: " << result.errorMessage() << '\n';
        exit(1);
    }
    if (help) {
        std::cout << cli;
        exit(0);
    }

    auto strat = blackjack::conceptify::optimizeBlackjack<blackjack::conceptify::BlackjackStrategyMap>(0);
    //std::cout << strat.toStringMat2() << "\n\n";
    auto deck = blackjack::conceptify::CountedDeck{0};
    double playResult = blackjack::conceptify::playBlackjack(N, strat, deck); 
    std::cout << "Result " << playResult << " after " << N << " hands played.\n";
    return 0;
}

