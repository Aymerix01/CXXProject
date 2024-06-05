#include "ShuffleCard.h"
#include <iostream>

using namespace std;

ShuffleCard::ShuffleCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : Card(node, eventCardManager)
{
	cout << "Shuffle card created: " << node.attribute("name").as_string() << endl;
}

void ShuffleCard::play()
{
	cout << "Shuffle card played: " << getName() << endl;
}

std::string ShuffleCard::getClassType() const
{
	return classType;
}

void ShuffleCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const
{
	//TODO Render
}

