#include "TaitPCH.h"
#include "GameAudio.h"
#include <Audioclient.h>

tait::GameAudio::GameAudio()
	: Audio()
{
}

void tait::GameAudio::StartPlayingSound(std::string& source)
{
	if (PlaySound(source.c_str(), nullptr, SND_SYNC))
		m_AudioSource.push_back(source.c_str());
}

void tait::GameAudio::StopPlayingSound(std::string& source)
{
	PlaySound(source.c_str(), nullptr, SND_PURGE);
}

void tait::GameAudio::StopAllSound()
{
	for(const LPCSTR& s: m_AudioSource)
	{ 
		PlaySound(s, nullptr, SND_PURGE);
	}
}
