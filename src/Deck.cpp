#include "Deck.h"
#include "ExplodingCard.h"
#include <iostream>
#include <algorithm>
#include <random> 

using namespace std;

Deck::Deck(const pugi::xml_node& node)
{
	pugi::xml_node n = node.first_child();
	buildCard(n);
	while (n != node.last_child()) {
		n = n.next_sibling();
		buildCard(n);
	}
}

void Deck::buildCard(const pugi::xml_node& node)
{
	if (string(node.name()) == "ExplodingCard") {
		auto c = make_unique<ExplodingCard>(node);
		cards.push_back(move(c));
	}
	else {
		cerr << "Unknown card type: " << node.name() << endl;
	}
}

void Deck::shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::ranges::shuffle(cards.begin(), cards.end(), g);
}

unique_ptr<Card> Deck::drawCard()
{
	//TODO: Implement the draw method
	return nullptr;
}

void Deck::addCardToEnd(unique_ptr<Card> card)
{
	//TODO: Implement the addCardToEnd method
}

vector<unique_ptr<Card>> Deck::showSomeCards(int nbCards)
{
	//TODO: Implement the showSomeCards method
	return vector<unique_ptr<Card>>();
}

bool Deck::empty() const
{
	//TODO: Implement the empty method
	return false;
}

