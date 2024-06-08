#pragma once
#include "MenuState.h"

class MenuPrincipal : public MenuState
{

public:
	explicit MenuPrincipal(MenuStateManager& m_manager);

	void render(sf::RenderWindow& window) override;
	void onUserEvent(sf::Event event, sf::RenderWindow& window) override;
};
