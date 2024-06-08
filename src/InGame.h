#pragma once
#include "MenuState.h"

class InGame : public MenuState
{
public:
	explicit InGame(MenuStateManager& m_manager);

	void render(sf::RenderWindow& window) override;
	void onUserEvent(sf::Event event, sf::RenderWindow& window) override;
};
