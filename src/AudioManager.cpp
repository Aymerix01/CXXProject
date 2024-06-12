#include "AudioManager.h"
#include <iostream>
#include <format>

using namespace std; 

AudioManager::AudioManager()
{
	std::string songToOpen;
	for (int i = 1; i <= 6; i++)
	{
		songToOpen = std::format("resources/OST--0{}.ogg",i);
		if (!osts[i].openFromFile(songToOpen))
		{
			cout << "Song: " << songToOpen << " Cannot be Loaded";
		}
	}
}

void AudioManager::playMusic(int i)
{
	osts[i].play();
}

void AudioManager::playSFX(int i)
{
	sfx[i].play();
}
