#pragma once
#include "Audio.h"
#include <iostream>
#include <string>

class LoggedAudio : public Audio
{
public:
	LoggedAudio(Audio& wrapped)
		: wrapped_(wrapped)
	{}

	void StartPlayingSound(std::wstring& soundID) override
	{
		log("play sound");
		wrapped_.StartPlayingSound(soundID);
	}

	void StopPlayingSound() override
	{
		log("stop sound");
		wrapped_.StopSound();
	}

	void StopAllSound() override
	{
		log("stop all sounds");
		wrapped_.StopAllSound();
	}

private:
	void log(const char* message)
	{
		// Code to log message...
		std::cout << "Logging message, imagine it being saved: " << message << std::endl;
	}

	Audio& wrapped_;
};