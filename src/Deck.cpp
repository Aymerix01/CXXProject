#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <random> 
#include "ExplodingCard.h"

using namespace std;

Deck::Deck(const pugi::xml_node& node, const sf::Sprite& sprite) :
	deckSprite(sprite)
{
	deckSprite.setPosition(deckPosition);
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

string Deck::dump() const
{
	string res;
	for (const auto& card : cards) {
		res += card->getName() + "\n";
	}
	return res;
}

void Deck::shuffle()
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::ranges::shuffle(cards.begin(), cards.end(), g);
}

unique_ptr<Card> Deck::drawCard()
{
	if (!cards.empty()) {
		auto card = move(cards.back());
		cards.pop_back();
		return card;
	}
	return nullptr;
}

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

bool Deck::empty() const
{
	if (cards.empty()) {
		return true;
	}
	return false;
}

void Deck::render(sf::RenderWindow& window) const
{
	window.draw(deckSprite);
}

