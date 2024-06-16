#pragma once
#include <SFML/Audio.hpp>


class AudioManager {
private:
	std::vector<std::unique_ptr<sf::Music>> osts;
	std::vector<std::unique_ptr<sf::SoundBuffer>> sfxBuffers;
	std::vector<sf::Sound> sfx;
	int songPlaying = 0; //Current song that is playing

public:
	/**
	* \brief Constructor that builds osts, sfxBuffers and sfx
	*/
	explicit AudioManager();

	/**
	* \brief Plays the current song defined by songPlaying
	*/
	void playMusic(); 
	
	/**
	* \brief Plays the correspoding sfx : SFX(i+1)
	* \brief SFX1 is CardPlayed ok
	* \brief SFX2 is CardShuffle ok
	* \brief SFX3 is BabyLaugh (attack) ok
	* \brief SFX4 is Defuse ok
	* \brief SFX5 is Explosion ok
	* \brief SFX6 is Future ok
	* \brief SFX7 is Happy
	*/
	void playSFX(int i);
	
	/**
	* \brief Returns wheter or not the current song has ended
	*/
	bool hasSongEnded();

	/**
	* \brief Passes to the next song
	*/
	void incrementSongToPlay(); 
};