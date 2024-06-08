#pragma once
#include "MenuState.h"

class MenuPause : public MenuState
{
public:
	explicit MenuPause(MenuStateManager& m_manager);

	void render(sf::RenderWindow& window) override;
	void onUserEvent(sf::Event event, sf::RenderWindow& window) override;
};