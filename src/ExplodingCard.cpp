#include "ExplodingCard.h"
#include <iostream>

using namespace std;

ExplodingCard::ExplodingCard(const pugi::xml_node& node) : Card(node)
{
	cout << "Exploding card created: " << name << endl;
}

void ExplodingCard::play()
{
	cout << "Exploding card played: " << name << endl;
}
