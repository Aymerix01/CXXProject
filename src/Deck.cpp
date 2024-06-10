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
	deckSprite(sprite), eventCardManager(eventCardManager)
{
	deckSprite.setPosition(deckPosition);
	pugi::xml_node n = node.first_child();
	buildCard(n, eventCardManager);
	while (n != node.last_child()) {
		n = n.next_sibling();
		buildCard(n, eventCardManager);
	}
}

void Deck::buildCard(const pugi::xml_node& node, EventCardManager& evntCrdMnger) {
	if (string(node.name()) == "ExplodingCard") {
		bombCard = make_unique<ExplodingCard>(node, evntCrdMnger);
	}
	else if (string(node.name()) == "AttackCard") {
		auto c = make_unique<AttackCard>(node, evntCrdMnger);
		cards.push_back(move(c));
	}
	else if (string(node.name()) == "DefuseCard") {
		defuseCard = make_unique<DefuseCard>(node, evntCrdMnger);
	}
	else if (string(node.name()) == "FutureCard") {
		auto c = make_unique<FutureCard>(node, evntCrdMnger);
		cards.push_back(move(c));
	}
	else if (string(node.name()) == "ShuffleCard") {
		auto c = make_unique<ShuffleCard>(node, evntCrdMnger);
		cards.push_back(move(c));
	}
	else if (string(node.name()) == "HappyCard") {
		auto c = make_unique<HappyCard>(node, evntCrdMnger);
		cards.push_back(move(c));
	}
	else {
		cerr << "Unknown card type: " << node.name() << endl;
	}
}

unique_ptr<Card> Deck::getDefuseCard() {
	return move(defuseCard);
}

void Deck::placeExplodingCard() {
	addCardToRandom(move(bombCard));
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

void Deck::moveFirstCardToRandom()
{
	if (!cards.empty()) {
		auto card = move(cards[0]);
		cards.erase(cards.begin());
		addCardToRandom(move(card));
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
	if(!cards.empty())
		window.draw(deckSprite);
}

void Deck::onEventCard(EventCard eventCard) {
	using enum EventCard;
	if (eventCard == ATTACK) {
		cout << "Deck: Attack event card" << endl;
		if (cards[cards.size() - 1]->getClassType() == "ExplodingCard") {
			cout << "Deck: Player gains points" << endl;
			eventCardManager.notifyEventCardListeners(EventCard::ATTACKPOINTS);
		}
		moveFirstCardToRandom();
	}
	else if (eventCard == SHUFFLE) {
		cout << "Deck: Shuffle event card" << endl;
		shuffle();
	}
	else if (eventCard == FUTURE) {
		//Il y a un problème ici, il faut afficher les 3 cartes retournées
		cout << "Deck: Future event card" << endl;
		showSomeCards(3);
	}
	
}
