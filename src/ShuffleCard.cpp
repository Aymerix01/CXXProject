#include "ShuffleCard.h"
#include <iostream>

using namespace std;

ShuffleCard::ShuffleCard(const pugi::xml_node& node) : Card(node)
{
	cout << "Shuffle card created: " << node.attribute("name").as_string() << endl;
}

int ShuffleCard::play(Deck& deck)
{
	cout << "Shuffle card played: " << getName() << endl;
	deck.shuffle();
	return 0;
}

std::string ShuffleCard::getClassType() const
{
	return classType;
}

void ShuffleCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const
{
	//TODO Render
}
