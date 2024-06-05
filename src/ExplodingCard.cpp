#include "ExplodingCard.h"
#include <iostream>

using namespace std;

ExplodingCard::ExplodingCard(const pugi::xml_node& node) : Card(node)
{
	cout << "Exploding card created: " << node.attribute("name").as_string() << endl;
}

int ExplodingCard::play(Deck& deck)
{
	cout << "Exploding card played: " << getName() << endl;
	return 0;
}

std::string ExplodingCard::getClassType() const
{
	return classType;
}

void ExplodingCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const {
	//TODO: Implement render
}
