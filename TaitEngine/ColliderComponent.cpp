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
	m_GameObject.GetTransform().SetSize(s);
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

void tait::ColliderComponent::SetIgnoreRight(bool ignore)
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

void tait::ColliderComponent::SetStatic(bool isStatic)
{
	m_IsStatic = isStatic;
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
#include "Time.h"
void tait::ColliderComponent::MoveBack(Transform& other, Vector& velocity)
{
	bool moveY{ IsFloatZero(velocity.x) };
	const Rect& otherRect = other.GetRect();
	if (!moveY)
	{
		float dt{ Time::GetInstance().GetDeltaTime() };
		//check left side
		if (velocity.x < 0)
		{
			const Vector p1{ otherRect.x, otherRect.y + velocity.y * dt + 1};
			const Vector p2{ otherRect.x, otherRect.y + otherRect.h - velocity.y * dt - 1};
			moveY = !(IsPointInRect(m_Coords, p1) && IsPointInRect(m_Coords, p2));
		}
		else
		{
			const Vector p1{ otherRect.x + otherRect.w, otherRect.y + velocity.y * dt + 1};
			const Vector p2{ otherRect.x + otherRect.w, otherRect.y + otherRect.h - velocity.y * dt - 1 };
			moveY = !(IsPointInRect(m_Coords, p1) && IsPointInRect(m_Coords, p2));
		}
	}

	if (moveY)
	{
		if (velocity.y > 0)
		{
			const Vector p1{ otherRect.x, otherRect.y + otherRect.h };
			const Vector p2{ otherRect.x + otherRect.w, otherRect.y + otherRect.h };
			Rect shortRect{ m_Coords.x, m_Coords.y, m_Coords.w, m_Coords.h / 3.f };
			if(IsPointInRect(shortRect, p1) || IsPointInRect(shortRect, p2))
			{
				other.SetPosition(Vector{ other.GetPosition().x, m_Coords.y - other.GetSize().y });
				velocity.y = 0;
			}
		}
		else
		{
			other.SetPosition(Vector{ other.GetPosition().x, m_Coords.y + m_Coords.h });
			velocity.y = 0;
		}
	}
	else
	{
		if (velocity.x > 0)
			other.SetPosition(Vector{ m_Coords.x - other.GetSize().x, other.GetPosition().y });
		else
			other.SetPosition(Vector{ m_Coords.x + m_Coords.w, other.GetPosition().y });
		velocity.x = 0;
	}
}

void tait::ColliderComponent::Update()
{
	if (!m_IsStatic)
	{
		m_Coords.x = m_GameObject.GetTransform().GetPosition().x;
		m_Coords.y = m_GameObject.GetTransform().GetPosition().y;
	}
}
