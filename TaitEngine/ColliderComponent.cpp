#include "TaitPCH.h"
#include "ColliderComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "EventSystem.h"

tait::ColliderComponent::ColliderComponent(GameObject& go)
	: Component(go)
	, m_Coords{}
	, m_Flag{}
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

void tait::ColliderComponent::SetIsTrigger(bool isTrigger)
{
	if (isTrigger)
		m_Flag |= 1 << 0;
	else
		m_Flag &= ~(1 << 0);
}

void tait::ColliderComponent::SetIgnoreUp(bool ignore)
{
	if (ignore)
		m_Flag |= 1 << 2;
	else
		m_Flag &= ~(1 << 2);
}

void tait::ColliderComponent::SetIgnoreDown(bool ignore)
{
	if (ignore)
		m_Flag |= 1 << 3;
	else
		m_Flag &= ~(1 << 3);
}

void tait::ColliderComponent::IgnoreRight(bool ignore)
{
	if (ignore)
		m_Flag |= 1 << 4;
	else
		m_Flag &= ~(1 << 4);
}

void tait::ColliderComponent::SetIgnoreLeft(bool ignore)
{
	if (ignore)
		m_Flag |= 1 << 5;
	else
		m_Flag &= ~(1 << 5);
}

bool tait::ColliderComponent::IgnoreCollision(const Vector& dir)
{
	if (dir.x > 0)
	{
		if ((m_Flag & (Flag::IgnoreRightVelocity)) != 0)
			return true;
	}
	else if (dir.x < 0)
	{
		if ((m_Flag & (Flag::IgnoreLeftVelocity)) != 0)
			return true;
	}
	if (dir.y > 0)
	{
		if ((m_Flag & (Flag::IgnoreDownVelocity)) != 0)
			return true;
	}
	if (dir.y < 0)
	{
		if ((m_Flag & (Flag::IgnoreUpvelocity)) != 0)
			return true;
	}
	return false;
}

void tait::ColliderComponent::MoveBack(Transform& other, const Vector& pos, Vector& velocity)
{
	float xDst{ pos.x - m_Coords.x };
	float yDst{ pos.y - m_Coords.y };

	if (xDst > m_Coords.w / 2.f)
		xDst = m_Coords.w - xDst;
	if (yDst > m_Coords.h / 2.f)
		yDst = m_Coords.h - yDst;
	if (yDst > xDst)
	{
		other.SetPosition(other.GetPosition() + Vector{ 0, yDst });
		velocity.y = 0;
	}
	else
	{
		other.SetPosition(other.GetPosition() + Vector{ xDst, 0 });
		velocity.x = 0;
	}
}
