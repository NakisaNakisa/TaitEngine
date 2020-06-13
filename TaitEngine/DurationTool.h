#pragma once

class DurationTool
{
public:
	bool Tick();
	bool IsActive();
	void SetTimes(float durationTime, float intervalTime = 0.f);
	void Activate();
private:
	float m_Duration, m_Interval;
	float m_DurationTimer, m_IntervalTimer;
};