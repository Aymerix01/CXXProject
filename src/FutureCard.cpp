#include "FutureCard.h"
#include <iostream>

using namespace std;

FutureCard::FutureCard(const pugi::xml_node& node, EventCardManager& eventCardManager) : Card(node, eventCardManager)
{
	cout << "Future card created: " << node.attribute("name").as_string() << endl;
}

void FutureCard::play()
{
	cout << "Future card played: " << getName() << endl;
}

std::string FutureCard::getClassType() const
{
	return classType;
}

void FutureCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const
{
	//TODO Render
}

