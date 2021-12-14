#pragma once

#include <string>
#include <vector>

namespace blackjack{

enum Rank52{
    Deuce,
    Three,
    Four,
    Five,
    Six,
    Seven,
    Eight,
    Nine,
    Ten,
    Jack,
    Queen,
    King,
    Ace,
};

std::string to_string(Rank52 rank);

enum Suit{
    Hearts,
    Diamonds,
    Spades,
    Clubs,
};

std::string to_string(Suit suit);

class Card52{
    public: 
        Card52(Rank52 rank, Suit suit);
        Card52(std::string const& str);
        Card52(int nb);
        Card52() = default;
        Card52(Card52 const&) = default;
        Card52& operator=(Card52 const&) = default;
        Card52(Card52&&) = default;
        Card52& operator=(Card52&&) = default;
    
        Rank52 rank() const;
        Suit suit() const;
        int nb() const;
        std::string toString() const;
        int toBlackjackScore() const;
        friend constexpr auto operator<=>(Card52 const& l, Card52 const& r) = default;
    private:    
        Rank52 rank_ = Deuce;
        Suit suit_ = Hearts;
};

std::vector<Card52> toCards(std::string const& str);

struct BlackjackRank{
    explicit BlackjackRank(Rank52);
    BlackjackRank() = default;
    BlackjackRank(BlackjackRank const&) = default;
    BlackjackRank& operator=(BlackjackRank const&) = default;
    BlackjackRank(BlackjackRank&&) = default;
    BlackjackRank& operator=(BlackjackRank&&) = default;
    int val = -1;
    static std::vector<BlackjackRank> createAll();
    friend constexpr auto operator<=>(BlackjackRank const& l, BlackjackRank const& r) = default;
    std::string toString() const;
    Card52 getRepresentativeCard() const;
};

}