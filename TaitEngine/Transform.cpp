#include "TaitPCH.h"
#include "Transform.h"

void tait::Transform::Translate(const Vector& delta)
{
	Vector newPos = m_Position + delta;
	SetPosition(newPos);
}

void tait::Transform::SetPosition(float x, float y)
{
	SetPosition(Vector{ x,y });
}

void tait::Transform::SetPosition(const Vector& p)
{
	m_Position = p;
	m_Center = p + m_HalfSize;
	m_Rect.x = p.x;
	m_Rect.y = p.y;
}

void tait::Transform::SetCenterPosition(float x, float y)
{
	SetCenterPosition(Vector{ x,y });
}

void tait::Transform::SetCenterPosition(const Vector& p)
{
	m_Position = p + (-m_HalfSize);
	m_Center = p;
	m_Rect.x = p.x - m_HalfSize.x;
	m_Rect.y = p.y - m_HalfSize.y;
}

void tait::Transform::SetSize(float w, float h)
{
	SetSize(Vector{ w,h });
}

void tait::Transform::SetSize(const Vector& s)
{
	m_HalfSize = s / 2;
	m_Size = s;
	m_Center = m_Position + m_HalfSize;
	m_Rect.w = s.x;
	m_Rect.h = s.y;
}

void tait::Transform::SetHalfSize(float w, float h)
{
	SetHalfSize(Vector{ w,h });
}

void tait::Transform::SetHalfSize(const Vector& s)
{
	m_HalfSize = s;
	m_Size = s * 2;
	m_Center = m_Position + m_HalfSize;
	m_Rect.w = s.x * 2;
	m_Rect.h = s.y * 2;
}
