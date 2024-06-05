#include "FutureCard.h"
#include <iostream>

using namespace std;

FutureCard::FutureCard(const pugi::xml_node& node) : Card(node)
{
	cout << "Future card created: " << node.attribute("name").as_string() << endl;
}

int FutureCard::play(Deck& deck)
{
	auto vector = deck.showSomeCards(3);
	return 0;
}

std::string FutureCard::getClassType() const
{
	return classType;
}

void FutureCard::render(sf::RenderWindow& window, const sf::Vector2f& position) const
{
	//TODO Render
}
