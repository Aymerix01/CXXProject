#include "AttackCard.h"
#include <iostream>

using namespace std;

AttackCard::AttackCard(const pugi::xml_node& node) : Card(node)
{
	cout << "Attack card created: " << node.attribute("name").as_string() << endl;
}

int AttackCard::play(Deck& deck)
{
	auto card = deck.attack();
	if (card == "ExplodingCard")
	{
		return 1000;
	}
	else
	{
		return 0;
	}
}

std::string AttackCard::getClassType() const
{
	return classType;
}

void AttackCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const
{
	//TODO Render
}
