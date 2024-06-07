#include "Game.hpp"
#include <iostream>
#include <pugixml.hpp>
#include <string>
#include "SFML/Graphics.hpp"

using namespace std;

int myMain()
{
    pugi::xml_document doc;
    if (auto result = doc.load_file("resources/Data.xml"); !result)
    {
        cerr << "Could not open file Data.xml because " << result.description() << endl;
        return 1;
    }

    pugi::xml_node root = doc.child("root");

    sf::Texture texturePlateau;
    if (!texturePlateau.loadFromFile("resources/TemplatePlateau.png")) {
        printf("Error loading texture\n");
        return -1;
    }
    sf::Sprite spritePlateau;
    spritePlateau.setTexture(texturePlateau);

    sf::Texture textureMenuPrincipal;
    if (!textureMenuPrincipal.loadFromFile("resources/FondMenuPrincipal.png")) {
        printf("Error loading texture\n");
        return -1;
    }
    sf::Sprite spriteMenuPrincipal;
    spriteMenuPrincipal.setTexture(textureMenuPrincipal);

    sf::Texture textureMenuCartes;
    if (!textureMenuCartes.loadFromFile("resources/MenuCartes.png")) {
        printf("Error loading texture\n");
        return -1;
    }
    sf::Sprite spriteMenuCartes;
    spriteMenuCartes.setTexture(textureMenuCartes);

    sf::Texture textureMenuPause;
    if (!textureMenuPause.loadFromFile("resources/MenuPause.png")) {
        printf("Error loading texture\n");
        return -1;
    }
    sf::Sprite spriteMenuPause;
    spriteMenuPause.setTexture(textureMenuPause);

    sf::Texture textureDosCarte;
    if (!textureDosCarte.loadFromFile("resources/DosCarte.png")) {
        printf("Error loading texture\n");
        return -1;
    }
    sf::Sprite spriteDosCarte;
    spriteDosCarte.setTexture(textureDosCarte);


    EventCardManager eventCardManager;

	Game game(string("Toto"), root, spritePlateau, spriteDosCarte, spriteMenuPrincipal, 
              spriteMenuCartes, spriteMenuPause, eventCardManager);
    game.run();

	return 0;
}
