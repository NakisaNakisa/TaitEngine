#pragma once
#include "Singleton.h"
#include <chrono>

namespace dae
{

	class Time final : public Singleton<Time>
	{
	public:
		//!!DO NOT CALL THIS FUNCTION!!
		void Update();
		int GetFPS() const;
		float GetDeltaTime() const;
	private:
		float m_DeltaTime{};
		float m_AccumulatedTime{};
		int m_FrameCounter{};
		int m_CurrentFPS{};
		std::chrono::time_point<std::chrono::steady_clock> m_LastTime;
	};

}
