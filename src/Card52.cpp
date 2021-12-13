#include "Card52.h" 

#include <range/v3/all.hpp>
#include <ranges>
#include <stdexcept>
#include <string>

namespace blackjack{

std::string to_string(Rank52 rank)
{
    switch (rank)
    {
        case Deuce: return "2";
        case Three: return "3";
        case Four: return "4";
        case Five: return "5";
        case Six: return "6";
        case Seven: return "7";
        case Eight: return "8";
        case Nine: return "9";
        case Ten: return "T";
        case Jack: return "J";
        case Queen: return "Q";
        case King: return "K";
        case Ace: return "A";    
    default:
        break;
    }
    return "Unknown";
}

std::string to_string(Suit suit)
{
    switch (suit)
    {
        case Hearts: return "h";
        case Diamonds: return "d";
        case Spades: return "s";
        case Clubs: return "c";
    default:
        break;
    }
    return "Unknown";
}

BlackjackRank::BlackjackRank(Rank52 rank)
{
    switch(rank){
        case Deuce: val = 2;
        case Three: val = 3;
        case Four: val = 4;
        case Five: val = 5;
        case Six: val = 6;
        case Seven: val = 7;
        case Eight: val = 8;
        case Nine: val = 9;
        case Ten: val = 10;
        case Jack: val = 10;
        case Queen: val = 10;
        case King: val = 10;
        case Ace: val = 11;    
    default:
        break;
    }
}

std::vector<BlackjackRank> BlackjackRank::createAll()
{
    return {BlackjackRank(Deuce),
    BlackjackRank(Three),
    BlackjackRank(Four),
    BlackjackRank(Five),
    BlackjackRank(Six),
    BlackjackRank(Seven),
    BlackjackRank(Eight),
    BlackjackRank(Nine),
    BlackjackRank(Ten),
    BlackjackRank(Ace),};
}

std::string BlackjackRank::toString() const
{
    return std::to_string(val);
}

Rank52 getRank(char c)
{
    switch(c){
        case '2': return Deuce;
        case '3': return Three;
        case '4': return Four;
        case '5': return Five;
        case '6': return Six;
        case '7': return Seven;
        case '8': return Eight;
        case '9': return Nine;
        case 'T': return Ten;
        case 'J': return Jack;
        case 'Q': return Queen;
        case 'K': return King;
        case 'A': return Ace;
        default: throw std::runtime_error("wrong input rank: " + std::to_string(c)); 
    }
    return Deuce;
}

Suit getSuit(char c)
{
    switch(c){
        case 'h': return Hearts;
        case 'd': return Diamonds;
        case 's': return Spades;
        case 'c': return Clubs;
        default: throw std::runtime_error("wrong input suit: " + std::to_string(c));
    }
    return Hearts;
}

Card52::Card52(Rank52 rank, Suit suit)
    : rank_(rank) , suit_(suit)
{}

Card52::Card52(std::string const& card)
    : rank_(getRank(card[0])) , suit_(getSuit(card[1]))
{}

Card52::Card52(int nb)
    : rank_(Rank52(nb % 13)), suit_(Suit(nb / 13))
{
    if(nb < 0 or nb > 51)
        throw std::runtime_error("Card52 out of range: " + std::to_string(nb) );
}
    
Rank52 Card52::rank() const
{
    return rank_;
}

Suit Card52::suit() const
{
    return suit_;
}

std::string Card52::toString() const
{
    std::string s;
    Rank52 r = rank();
    Suit su = suit();
    s += blackjack::to_string(r);
    s += blackjack::to_string(su);
    return s;
}

int Card52::toBlackjackScore() const
{
    switch (rank_)
    {
        case Deuce: return 2;
        case Three: return 3;
        case Four: return 4;
        case Five: return 5;
        case Six: return 6;
        case Seven: return 7;
        case Eight: return 8;
        case Nine: return 9;
        case Ten: return 10;
        case Jack: return 10;
        case Queen: return 10;
        case King: return 10;
        case Ace: return 1;  // case eleven is handled outside  
    default:
        break;
    }
    return -1;
}


std::vector<Card52> toCards(std::string const& str)
{
    auto cardsStr =  str | ranges::views::split(' ')
                         | ranges::views::transform([](auto &&rng) {
        return std::string(&*rng.begin(), std::ranges::distance(rng));
    });
    std::vector<Card52> ret;
    for(auto const& card : cardsStr)
        ret.push_back(Card52(card));
    return ret; 
}

}