#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <random> 
#include <math.h>

using namespace std;

Deck::Deck(EventCardManager& eventCardManager) :
	eventCardManager(eventCardManager)
{
	if (!textureDosCarte.loadFromFile("resources/DosCarte.png") )
	{
			printf("Error loading texture\n");
	}
	deckSprite.setTexture(textureDosCarte);

	if (auto result = doc.load_file("resources/Data.xml"); !result)
	{
		cerr << "Could not open file Data.xml because " << result.description() << endl;
	}
	root = doc.child("root");

	buildDeck();
}

void Deck::buildDeck() {
	deckSprite.setPosition(deckPosition);
	pugi::xml_node n = root.first_child();
	buildCard(n, eventCardManager);
	while (n != root.last_child()) {
		n = n.next_sibling();
		buildCard(n, eventCardManager);
	}
}

void Deck::buildCard(const pugi::xml_node& node, EventCardManager& evntCrdMnger) {
	if (string(node.name()) == "ExplodingCard") {
		bombCard = make_unique<Card>(node, evntCrdMnger);
	}
	else if (string(node.name()) == "AttackCard") {
		auto c = make_unique<Card>(node, evntCrdMnger);
		cards.push_back(move(c));
	}
	else if (string(node.name()) == "DefuseCard") {
		defuseCard = make_unique<Card>(node, evntCrdMnger);
	}
	else if (string(node.name()) == "FutureCard") {
		auto c = make_unique<Card>(node, evntCrdMnger);
		cards.push_back(move(c));
	}
	else if (string(node.name()) == "ShuffleCard") {
		auto c = make_unique<Card>(node, evntCrdMnger);
		cards.push_back(move(c));
	}
	else if (string(node.name()) == "HappyCard") {
		auto c = make_unique<Card>(node, evntCrdMnger);
		cards.push_back(move(c));
	}
	else {
		cerr << "Unknown card type: " << node.name() << endl;
	}
}

unique_ptr<Card> Deck::getDefuseCard() {
	return move(defuseCard);
}

unique_ptr<Card> Deck::getExplodingCard() {
	return move(bombCard);
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
	am.playSFX(1);
	std::random_device rd;
	std::mt19937 g(rd());

	std::ranges::shuffle(cards.begin(), cards.end(), g);
}

unique_ptr<Card> Deck::drawCard()
{
	renderTopCard = false;
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
		auto card = move(cards[cards.size()-1]);
		cards.pop_back();
		addCardToRandom(move(card));
	}
}

vector<Card*> Deck::showSomeCards(int nbCards)
{
	am.playSFX(5);
	if (!cards.empty()) {
		vector<Card*> res;
		for (int i = 0; i < min(nbCards, static_cast<int>(cards.size())); i++) {
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

void Deck::render(sf::RenderWindow& window)
{
	if(!cards.empty())
		window.draw(deckSprite);
	if (renderTopCard) {
		std::vector<Card*> showCards = showSomeCards(3);
		for (int i = 0; i < showCards.size(); i++) {
			showCards[i]->render(window, sf::Vector2f(static_cast<float>(100 + i * 200), 75), sf::Vector2f(0.5, 0.5));
		}
	}
}

void Deck::onEventCard(EventCard eventCard) {
	using enum EventCard;
	if (eventCard == ATTACK) {
		cout << "Deck: Attack event card" << endl;
		if (cards[cards.size() - 1]->getClassType() == "ExplodingCard") {
			am.playSFX(2);
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
		cout << "Deck: Future event card" << endl;
		renderTopCard = true;
	}
}

void Deck::reset()
{
	cards.clear();
	buildDeck();
}
