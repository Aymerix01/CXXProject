#pragma once

#include "MenuState.h"

class MenuFin : public MenuState
{
public:
	explicit MenuFin(MenuStateManager& m_manager);

	void render(sf::RenderWindow& window) override;
	void onUserEvent(sf::Event event, sf::RenderWindow& window) override;
};
