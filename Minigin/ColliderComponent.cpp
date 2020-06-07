#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "EventSystem.h"

tait::ColliderComponent::ColliderComponent(GameObject& go)
	: Component(go)
	, m_Coords{}
	, m_IsTrigger{ false }
{
}

void tait::ColliderComponent::SetPos(const Vector& p)
{
	m_Coords.x = p.x;
	m_Coords.y = p.y;
}

void tait::ColliderComponent::SetSize(const Vector& s)
{
	m_Coords.w = s.x;
	m_Coords.h = s.y;
}

void tait::ColliderComponent::SetRect(const Rect& r)
{
	m_Coords = r;
}

bool tait::ColliderComponent::IsColliding(const Vector& start, const Vector& end, Vector& hit)
{
	if (IsPointInRect(m_Coords, end))
	{
		if (!m_IsTrigger)
		{
			Vector dir = end + (-start);
			dir.x = dir.x / abs(dir.x);
			dir.y = dir.y / abs(dir.y);
			hit.x = m_Coords.x + m_Coords.w / 2.f * dir.x;
			hit.y = m_Coords.y + m_Coords.h / 2.f * dir.y;
		}
		CollisionIsOccuring(true);
		return true;
	}
	CollisionIsOccuring(false);
	return false;
}

void tait::ColliderComponent::CollisionIsOccuring(bool isColliding)
{
	if (isColliding)
	{
		if (m_IsColliding)
			EventSystem::TriggerEvent(*this, Event::TRIGGER_INSIDE);
		else
			EventSystem::TriggerEvent(*this, Event::TRIGGER_ENTERED);
		m_IsColliding = true;
	}
	else
	{
		if (m_IsColliding)
		{
			EventSystem::TriggerEvent(*this, Event::TRIGGER_EXIT);
			m_IsColliding = false;
		}
	}
}
