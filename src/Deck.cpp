#include "Deck.h"
#include "ExplodingCard.h"
#include <iostream>
#include <algorithm>
#include <random> 

using namespace std;

/**
* \brief Constructor of the Deck class
* \param node : pugi::xml_node
*/
Deck::Deck(const pugi::xml_node& node)
{
	pugi::xml_node n = node.first_child();
	buildCard(n);
	while (n != node.last_child()) {
		n = n.next_sibling();
		buildCard(n);
	}
}

/**
* \brief Add a card to the deck
* \param node : pugi::xml_node
*/
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

/**
* \brief Dump the deck
* \return string
*/
string Deck::dump() const
{
	string res;
	for (const auto& card : cards) {
		res += card->getName() + "\n";
	}
	return res;
}

/**
* \brief Shuffle the deck
*/
void Deck::shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::ranges::shuffle(cards.begin(), cards.end(), g);
}

/**
* \brief Draw the last card from the deck (cards.back())
* \return unique_ptr<Card>
*/
unique_ptr<Card> Deck::drawCard()
{
	if (!cards.empty()) {
		auto card = move(cards.back());
		cards.pop_back();
		return card;
	}
	return nullptr;
}

/**
* \brief Add a card to the deck at a random position
* \param card : unique_ptr<Card>
*/
void Deck::addCardToRandom(unique_ptr<Card> card)
{
	if (cards.empty()) {
		cards.push_back(move(card));
	}
	else {
		std::random_device rd;
		std::mt19937 g(rd());
		std::uniform_int_distribution dist(0, static_cast<int>(cards.size()) - 1);
		cards.insert(cards.begin() + dist(g), move(card));
	}
}

/**
* \brief Show the nbCards first cards of the deck
* \param card : unique_ptr<Card>
* \return vector<Card*> : vector of observed cards
*/
vector<Card*> Deck::showSomeCards(int nbCards)
{
	if (!cards.empty()) {
		vector<Card*> res;
		for (int i = 0; i < nbCards; i++) {
			res.push_back(cards[i].get());
		}
		return res;
	}
	return vector<Card*>();
}

/**
* \brief Show if the deck is empty
* \return bool
*/
bool Deck::empty() const
{
	if (cards.empty()) {
		return true;
	}
	return false;
}

