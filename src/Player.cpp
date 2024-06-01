#include "Player.h"
#include <iostream>

using namespace std;

/**
* \brief Constructor of the Player class
* \param name : string
*/
Player::Player(const string& name) : 
	playerName(name)
{
}

/**
* \brief Draw a card from the deck
* \param deck : Deck&
*/
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

/**
* \brief Show the player's cards
*/
void Player::showHand() const
{
	int index = 0;
	for (const auto& card : hand)
	{
		cout << index << " : " << card->getName() << endl;
		index++;
	}
}

/**
* \brief Play a card
* \param card : unique_ptr<Card>
*/
void Player::playCard(int index, Deck& deck)
{
	hand[index]->play();
	hand.erase(hand.begin() + index);
}

/**
* \brief Check if the player has lost
* \return bool
*/
bool Player::hasLost() const
{
	//TODO: Implement this function
	return false;
}

