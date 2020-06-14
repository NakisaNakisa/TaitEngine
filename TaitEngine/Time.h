#pragma once
#include "Singleton.h"
#include <chrono>

namespace tait
{

	class Time final : public Singleton<Time>
	{
	public:
		void Create();
		//!!DO NOT CALL THIS FUNCTION!! //Ugly design, I know :-/
		void Update();
		int GetFPS() const;
		float GetDeltaTime() const;
		void ToggleTime();
	private:
		std::chrono::time_point<std::chrono::steady_clock> m_LastTime;
		float m_DeltaTime{};
		float m_AccumulatedTime{};
		int m_FrameCounter{};
		int m_CurrentFPS{};
		bool m_IsTimeRunning{ true };
	};

}
