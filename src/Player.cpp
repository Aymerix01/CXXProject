#include "Player.h"

using namespace std;

Player::Player(const string& name) : 
	playerName(name)
{
}

void Player::drawCard(Deck& deck)
{
	//TODO: Implement the drawCard method
}

void Player::playCard(unique_ptr<Card> card)
{
	//TODO: Implement the playCard method
}

bool Player::hasLost() const
{
	//TODO: Implement the hasLost method
	return false;
}

