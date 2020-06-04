#include "MiniginPCH.h"
#include "Time.h"
#include <chrono>

using namespace std;
using namespace chrono;

void dae::Time::Update()
{
	const auto currentTime = std::chrono::high_resolution_clock::now(); 
	m_DeltaTime = std::chrono::duration<float>(currentTime - m_LastTime).count();
	m_LastTime = currentTime;
	m_AccumulatedTime += m_DeltaTime;
	m_FrameCounter++;
	if (m_AccumulatedTime >= 1)
	{
		m_CurrentFPS = m_FrameCounter;
		m_FrameCounter = 0;
		m_AccumulatedTime -= 1;
		//Slightly ugly fix for time going ham
		if (m_AccumulatedTime > 2)
			m_AccumulatedTime = 0;
	}
}

int dae::Time::GetFPS() const
{
	return m_CurrentFPS;
}

float dae::Time::GetDeltaTime() const
{
	return m_DeltaTime;
}
