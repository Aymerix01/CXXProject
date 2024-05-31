#include "Deck.h"
#include <pugixml.hpp>

Deck::Deck()
{
	//TODO: Implement the Deck constructor
}

void Deck::shuffle()
{
	//TODO: Implement the shuffle method
}

std::unique_ptr<Card> Deck::drawCard()
{
	//TODO: Implement the draw method
	return nullptr;
}

void Deck::addCardToEnd(std::unique_ptr<Card> card)
{
	//TODO: Implement the addCardToEnd method
}

std::vector<std::unique_ptr<Card>> Deck::showSomeCards(int nbCards)
{
	//TODO: Implement the showSomeCards method
	return std::vector<std::unique_ptr<Card>>();
}

bool Deck::empty() const
{
	//TODO: Implement the empty method
	return false;
}

