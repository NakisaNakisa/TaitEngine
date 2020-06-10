#pragma once
#include "NullAudio.h"

class Locator
{
public:
	static void Cleanup()
	{
		delete m_NullService;
	}

	static void Initialize()
	{
		m_NullService = new tait::NullAudio();
		m_Service = m_NullService;
	}

	static tait::Audio& GetAudio() { return *m_Service; }

	static void Provide(tait::Audio* service)
	{
		if (service == nullptr)
		{
			// Revert to null service.
			m_Service = m_NullService;
		}
		else
		{
			m_Service = service;
		}
	}

private:
	static tait::Audio* m_Service;
	static tait::NullAudio* m_NullService;
};

tait::Audio* Locator::m_Service = nullptr;
tait::NullAudio* Locator::m_NullService = nullptr;