#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <random> 
#include "ExplodingCard.h"
#include "ShuffleCard.h"
#include "HappyCard.h"
#include "AttackCard.h"
#include "DefuseCard.h"
#include "FutureCard.h"


using namespace std;

Deck::Deck(const pugi::xml_node& node, const sf::Sprite& sprite, EventCardManager& eventCardManager) :
	deckSprite(sprite)
{
	deckSprite.setPosition(deckPosition);
	pugi::xml_node n = node.first_child();
	buildCard(n, eventCardManager);
	while (n != node.last_child()) {
		n = n.next_sibling();
		buildCard(n, eventCardManager);
	}
}

void Deck::buildCard(const pugi::xml_node& node, EventCardManager& eventCardManager) {
	if (string(node.name()) == "ExplodingCard") {
		auto c = make_unique<ExplodingCard>(node, eventCardManager);
		cards.push_back(move(c));
	}
	else if (string(node.name()) == "AttackCard") {
		auto c = make_unique<AttackCard>(node, eventCardManager);
		cards.push_back(move(c));
	}
	else if (string(node.name()) == "DefuseCard") {
		auto c = make_unique<DefuseCard>(node, eventCardManager);
		cards.push_back(move(c));
	}
	else if (string(node.name()) == "FutureCard") {
		auto c = make_unique<FutureCard>(node, eventCardManager);
		cards.push_back(move(c));
	}
	else if (string(node.name()) == "ShuffleCard") {
		auto c = make_unique<ShuffleCard>(node, eventCardManager);
		cards.push_back(move(c));
	}
	else if (string(node.name()) == "HappyCard") {
		auto c = make_unique<HappyCard>(node, eventCardManager);
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

string Deck::attack()
{
	if (!cards.empty()) {
		auto card = move(cards.back());
		auto str = card->getClassType();
		cards.pop_back();
		addCardToRandom(move(card));

		return str;
	}
	return " ";
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
			res.push_back(cards[cards.size() - i -1].get());
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

void Deck::onEventCard() {
	//TODO : implement onEventCard
}
