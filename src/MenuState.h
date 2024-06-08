#pragma once

#include "SFML/Graphics.hpp"

class MenuStateManager;
class MenuState
{

protected:
	MenuStateManager& m_manager; 
	
public:
	explicit MenuState(MenuStateManager& m_manager);
	virtual ~MenuState() = default;

	virtual void render(sf::RenderWindow& window) = 0;
	virtual void onUserEvent(sf::Event event, sf::RenderWindow& window) = 0;
};