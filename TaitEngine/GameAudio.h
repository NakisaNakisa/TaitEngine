#pragma once
#include "Audio.h"
#include <string>
#include <Windows.h>
#include <mmsystem.h>

namespace tait
{
	class GameAudio : public Audio
	{
	public:
		GameAudio();
		void StartPlayingSound(std::string& source) override;
		void StopPlayingSound(std::string& source) override;
		void StopAllSound() override;
	private:
		std::vector<LPCSTR> m_AudioSource{};
	};
}