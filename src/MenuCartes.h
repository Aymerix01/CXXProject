#pragma once
#include "MenuState.h"

class MenuCartes : public MenuState
{
public:
	explicit MenuCartes(MenuStateManager& m_manager);

	void render(sf::RenderWindow& window) override;
	void onUserEvent(sf::Event event, sf::RenderWindow& window) override;
};
