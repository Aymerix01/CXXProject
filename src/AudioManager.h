#pragma once
#include <SFML/Audio.hpp>


class AudioManager {
private:
	std::vector<std::unique_ptr<sf::Music>> osts;
	std::vector<std::unique_ptr<sf::SoundBuffer>> sfxBuffers;
	std::vector<sf::Sound> sfx;
	
	//SFX1 is CardPlayed
	//SFX2 is CardShuffle
	//SFX3 is BabyLaugh (attack)
	//SFX4 is Defuse
	//SFX5 is Explosion
	//SFX6 is Future
	//SFX7 is Happy

public:
	explicit AudioManager();
	void playMusic(int i);
	void playSFX(int i);
};