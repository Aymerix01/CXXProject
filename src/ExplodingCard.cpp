#include "ExplodingCard.h"
#include <iostream>

ExplodingCard::ExplodingCard(const std::string& name) :
	name(name)
{
}

void ExplodingCard::play()
{
	std::cout << "Exploding card played: " << name << std::endl;
}
