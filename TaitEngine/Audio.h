#pragma once
#include <string>

namespace tait
{
	class Audio
	{
	public:
		virtual ~Audio() {};
		virtual void StartPlayingSound(std::string& source) = 0;
		virtual void StopPlayingSound(std::string& source) = 0;
		virtual void StopAllSound() = 0;
	};
}