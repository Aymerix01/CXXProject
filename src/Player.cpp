#include "Player.h"
#include <iostream>
#include <math.h>

using namespace std;

Player::Player(const string& name) : 
	playerName(name)
{
}

void Player::drawCard(Deck& deck)
{
	if(!deck.empty())
	{ 
		hand.push_back(deck.drawCard());
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

void Player::playCard(int index, Deck& deck)
{
	hand[index]->play(deck);
	hand.erase(hand.begin() + index);
}

bool Player::hasLost() const
{
	bool getExplodingCard = false;
	bool getDefuseCard = false;
	for (const auto& card : hand)
	{
		if (card->getClassType() == "ExplodingCard")
		{
			getExplodingCard = true;
		}
		if (card->getClassType() == "DefuseCard")
		{
			getDefuseCard = true;
		}
		if (getExplodingCard && getDefuseCard)
		{
			return false;
		}
	}
	if (getExplodingCard && !getDefuseCard)
	{
		return true;
	}
	return false;
}

void Player::renderHand(sf::RenderWindow& window) const
{
	auto position = sf::Vector2f(static_cast<float>(window.getSize().x/2 - 400), 715);
	int index = 0;
	for (const auto& card : hand)
	{
		card->render(window, position);
		position.x += 400 / static_cast<float>(index + 1);
		index++;

	}
}

