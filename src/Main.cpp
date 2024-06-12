#include "Game.hpp"
#include <iostream>
#include <pugixml.hpp>
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

int myMain()
{
    EventCardManager eventCardManager;

	Game game(string("Toto"), eventCardManager);
    game.run();

	return 0;
}
