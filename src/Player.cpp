#include "Player.h"
#include <iostream>
#include <math.h>
#include <format>

using namespace std;

Player::Player(const string& name) : 
	playerName(name)
{
	fontScore.loadFromFile("media/Sansation.ttf");
	textScore.setFont(fontScore);
	textScore.setCharacterSize(50);
	textScore.setPosition(900, 60);
}

void Player::getDefuseCard(Deck& deck) {
	hand.push_back(deck.getDefuseCard());
}

void Player::getExplodingCard(Deck& deck) {
	hand.push_back(deck.getExplodingCard());
}

void Player::drawCard(Deck& deck)
{
	lastPlayedCards.clear();
	if(!deck.empty())
	{ 
		auto card = deck.drawCard();
		hand.push_back(move(card));
	}
	else
	{
		cout << "Deck is empty" << endl;
	}
}

void Player::showHand() const
{
	int index = 0;
	for (const auto& card : hand)
	{
		cout << index << " : " << card->getName() << endl;
		index++;
	}
}

string Player::dump() const
{
	string res;
	for (const auto& card : hand) {
		res += card->getName() + "\n";
	}
	return res;
}

void Player::playCard(int index)
{
	am.playSFX(0);
	hand[index]->play();
	lastPlayedCards.push_back(move(hand[index]));
	hand.erase(hand.begin() + index);
}

bool Player::hasLost(Deck& deck)
{
	bool getExplodingCard = false;
	bool getDefuseCard = false;
	int indexExplodingCard = -1;
	int indexDefuseCard = -1;
	int index = 0;
	for (const auto& card : hand)
	{
		if (getExplodingCard && getDefuseCard)
		{
			am.playSFX(3);
			cout << "Remove exploding card and defuse card from hand" << endl;
			auto explodingCard = move(hand[indexExplodingCard]);
			deck.addCardToRandom(move(explodingCard));
			hand.erase(hand.begin() + max(indexExplodingCard, indexDefuseCard));
			hand.erase(hand.begin() + min(indexExplodingCard, indexDefuseCard));
			return false;
		}
		if (card->getClassType() == "ExplodingCard")
		{
			getExplodingCard = true;
			indexExplodingCard = index;
		}
		if (card->getClassType() == "DefuseCard")
		{
			getDefuseCard = true;
			indexDefuseCard = index;
		}
		index++;
	}
	if (getExplodingCard && getDefuseCard)
	{
		cout << "Remove exploding card and defuse card from hand" << endl;
		auto explodingCard = move(hand[indexExplodingCard]);
		deck.addCardToRandom(move(explodingCard));
		hand.erase(hand.begin() + max(indexExplodingCard, indexDefuseCard));
		hand.erase(hand.begin() + min(indexExplodingCard, indexDefuseCard));
		return false;
	}
	else if (getExplodingCard && !getDefuseCard)
	{
		return true;
	}
	return false;
}

void Player::renderHand(sf::RenderWindow& window, sf::Vector2i mousePos, bool playerDragDrop)
{
	auto position = sf::Vector2f(static_cast<float>(window.getSize().x/2 - 475), 715);
	
	int indexCardHovered = -1;
	int index = 0;
	bool cardHovered = false;
	for (const auto& card : hand)
	{
		if (static_cast<float>(mousePos.x) >= position.x && 
			static_cast<float>(mousePos.x) <= position.x + 800 / static_cast<float>(hand.size()) &&
			static_cast<float>(mousePos.y) >= position.y &&
			static_cast<float>(mousePos.y) <= position.y + 291)
		{
			indexCardHovered = index;
			cardHovered = true;
		}
		else
		{
			if (index != indexSelectedCard)
			{
				card->render(window, position, { 1, 1 });
			}
		}
		position.x += 800 / static_cast<float>(hand.size());
		index++;
	}
	if (!playerDragDrop && indexSelectedCard != -1 && mousePos.y < 400) {
		playCard(indexSelectedCard);
		indexSelectedCard = -1;
	}
	else if (!playerDragDrop && indexSelectedCard != -1) {
		indexSelectedCard = -1;
	}
	else if (indexSelectedCard != -1) {
		float cardPosX = static_cast<float>(mousePos.x) - 50;
		float cardPosY = static_cast<float>(mousePos.y) - 145;
		hand[indexSelectedCard]->render(window, { cardPosX, cardPosY }, { 1, 1} );
	}
	else if (playerDragDrop && cardHovered) {
		indexSelectedCard = indexCardHovered;
	}
	else if (cardHovered)
	{
		auto newPos = sf::Vector2f(static_cast<float>(window.getSize().x / 2 - 100), 600);
		hand[indexCardHovered]->render(window, newPos, { 1.2f, 1.2f });
	}
}

void Player::renderScore(sf::RenderWindow& window)
{
	textScore.setString(to_string(score));
	window.draw(textScore);
}

void Player::renderScoreEndGame(sf::RenderWindow& window) {
	textScore.setString(to_string(score));
	textScore.setPosition(875, 300);
	textScore.setCharacterSize(100);
	window.draw(textScore);
}

void Player::renderPlayedCard(sf::RenderWindow& window) const
{
	auto position = sf::Vector2f(static_cast<float>(window.getSize().x / 2) - 1000.f, 250);
	for(const auto& card : lastPlayedCards)
	{
		position.x += 1600 / static_cast<float>(lastPlayedCards.size() + 1);
		card->render(window, position, {1, 1});
	}
}

void Player::onEventCard(EventCard eventCard)
{
	if (eventCard == EventCard::HAPPYPOINTS) {
		cout << playerName << " has gained 100 points" << endl;
		addPoints(100);
	}
	else if (eventCard == EventCard::ATTACKPOINTS) {
		cout << playerName << " has gained 1000 points" << endl;
		addPoints(1000);
	}
}

void Player::reset()
{
	textScore.setCharacterSize(50);
	textScore.setPosition(900, 60);
	hand.clear();
	lastPlayedCards.clear();
	score = 0;
}


