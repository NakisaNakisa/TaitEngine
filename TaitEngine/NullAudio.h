#pragma once
#include "Audio.h"

namespace tait
{
	class NullAudio : public Audio
	{
	public:
		void StartPlayingSound(std::string&) override {}
		void StopPlayingSound(std::string&) override {}
		void StopAllSound() override {}
	};
}