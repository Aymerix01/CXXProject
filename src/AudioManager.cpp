#include "AudioManager.h"
#include <iostream>
#include <format>

using namespace std; 

AudioManager::AudioManager()
{
	osts.reserve(6);
	std::string songToOpen;
	for (int i = 1; i <= 6; i++)
	{
		auto music = std::make_unique<sf::Music>();
		songToOpen = std::format("resources/OST--0{}.ogg",i);
		if (!music->openFromFile(songToOpen))
		{
			cout << "Song: " << songToOpen << " Cannot be Loaded";
		}
		else {
			osts.push_back(std::move(music));
		}
	}

	sfxBuffers.reserve(7);
	sfx.reserve(7);
	for (int i = 1; i <= 7; i++)
	{
		auto buffer = std::make_unique<sf::SoundBuffer>();
		std::string sfxFile = std::format("resources/SFX{}.mp3", i);
		if (!buffer->loadFromFile(sfxFile))
		{
			cout << "Sound effect: " << sfxFile << " Cannot be Loaded" << endl;
		}
		else
		{
			sfxBuffers.push_back(std::move(buffer));
			sf::Sound sound;
			sound.setBuffer(*sfxBuffers.back());
			sfx.push_back(sound);
		}
	}
}

void AudioManager::playMusic(int i)
{
	if (i >= 0 && i < osts.size() && osts[i])
	{
		osts[i]->play();
	}
	else {
		cout << "Invalid music index: " << i << endl;
	}
	
}

void AudioManager::playSFX(int i)
{
	if (i >= 0 && i < sfx.size())
	{
		sfx[i].play();
	}
	else
	{
		cout << "Invalid SFX index: " << i << endl;
	}
}
