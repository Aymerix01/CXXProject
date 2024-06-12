#pragma once
#include <SFML/Audio.hpp>


class AudioManager {
private:
	std::vector<sf::Music> osts;
	std::vector<sf::Sound> sfx;

public:
	explicit AudioManager();
	void playMusic(int i);
	void playSFX(int i);
};