#pragma once
#include "Audio.h"
#include <iostream>
#include <string>

namespace tait
{
	class LoggedAudio : public Audio
	{
	public:
		LoggedAudio(Audio& wrapped)
			: wrapped_(wrapped)
		{}

		void StartPlayingSound(std::string& source) override 
		{
			log("play sound");
			wrapped_.StartPlayingSound(source);
		}
		virtual void StopPlayingSound(std::string& source) override
		{
			log("stop sound");
			wrapped_.StopPlayingSound(source);
		}
		virtual void StopAllSound() override
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
}