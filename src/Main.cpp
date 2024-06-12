#include "Game.hpp"
#include <iostream>
#include <pugixml.hpp>
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

int myMain()
{
	Game game(string("Toto"));
    game.run();

	return 0;
}
