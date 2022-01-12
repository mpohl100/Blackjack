
#include "BlackjackAnalysis.h"

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

    std::cout << "Hello" << '\n';
    for(int i = -10; i <= 10; ++i)
    {
        BlackjackStrategy strat = optimizeBlackjack(i);
        std::cout << "Card count " << i << '\n';
        std::cout << strat.toStringMat2() << "\n\n"; 
    }
    return 0;
}

