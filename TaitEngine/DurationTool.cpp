#include "TaitPCH.h"
#include "DurationTool.h"
#include "Time.h"

bool DurationTool::Tick()
{
	float dt = tait::Time::GetInstance().GetDeltaTime();
	m_DurationTimer -= dt;
	m_IntervalTimer -= dt;
	if (m_IntervalTimer <= 0)
	{
		m_IntervalTimer = m_Interval;
		return true;
	}
	return false;
}

bool DurationTool::IsActive()
{
	return m_DurationTimer > 0;
}

void DurationTool::SetTimes(float durationTime, float intervalTime)
{
	m_Duration = durationTime;
	m_Interval = intervalTime;
}

void DurationTool::Activate()
{
	m_DurationTimer = m_Duration;
	m_IntervalTimer = m_Interval;
}
