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

    sf::Texture textureDosCarte;
    if (!textureDosCarte.loadFromFile("resources/DosCarte.png")) {
        printf("Error loading texture\n");
        return -1;
    }
    sf::Sprite spriteDosCarte;
    spriteDosCarte.setTexture(textureDosCarte);

    sf::Texture texturePlateau;
    if (!texturePlateau.loadFromFile("resources/TemplatePlateau.png")) {
        printf("Error loading texture\n");
    }
    sf::Sprite backgroundSprite;
    backgroundSprite.setTexture(texturePlateau);

    sf::Texture textureMenuPrincipal;
    if (!textureMenuPrincipal.loadFromFile("resources/FondMenuPrincipal.png")) {
        printf("Error loading texture\n");
    }
    sf::Sprite menuPrincipalSprite;
    menuPrincipalSprite.setTexture(textureMenuPrincipal);

    sf::Texture textureMenuCartes;
    if (!textureMenuCartes.loadFromFile("resources/MenuCartes.png")) {
        printf("Error loading texture\n");
    }
    sf::Sprite menuCartesSprite;
    menuCartesSprite.setTexture(textureMenuCartes);

    sf::Texture textureMenuPause;
    if (!textureMenuPause.loadFromFile("resources/MenuPause.png")) {
        printf("Error loading texture\n");
    }
    sf::Sprite menuPauseSprite;
    menuPauseSprite.setTexture(textureMenuPause);

    sf::Texture textureMenuFin;
    if (!textureMenuFin.loadFromFile("resources/MenuEndGame.png")) {
        printf("Error loading texture\n");
    }
    sf::Sprite menuFinSprite;
    menuFinSprite.setTexture(textureMenuFin);

    EventCardManager eventCardManager;

	Game game(string("Toto"), root, backgroundSprite, menuPrincipalSprite, menuCartesSprite,
              menuPauseSprite, menuFinSprite, spriteDosCarte, eventCardManager);
    game.run();

	return 0;
}
