#pragma once

#include "BlackjackSituation.h"
#include "Card52.h"

#include "evol/Rng.h"

#include <concepts>


namespace blackjack{

template<class T>
concept DeckConcept = std::semiregular<T> && requires(const T t)
{
    {t.getCount()} -> std::same_as<int>;
    {t.getNumberCards()} -> std::same_as<int>;
}
&& requires(T t, const evol::Rng& rng){
    {t.getCard(rng)} -> std::same_as<Card52>;
};

template<class T, class D>
concept BlackjackStrategyConcept = std::semiregular<T> && DeckConcept<D> && requires (const T t, HandSituation handSituation, SplitSituation splitSituation, D deck)
{
    {t.getDraw(handSituation, deck)} -> std::same_as<bool>;
    {t.getDoubleDown(handSituation, deck)} -> std::same_as<bool>;
    {t.getSplit(splitSituation, deck)} -> std::same_as<bool>;
}
&& requires(const T t, HandSituation handSituation, SplitSituation splitSituation, bool doIt)
{
    {t.addDraw(handSituation, doIt)};
    {t.addDoubleDown(handSituation, doIt)};
    {t.addSplit(splitSituation, doIt)};

};
}