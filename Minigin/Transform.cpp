#include "MiniginPCH.h"
#include "Transform.h"

void dae::Transform::CalculateTRS()
{
	m_TRS = GetTrsMatrix(m_Position, m_Rotation, m_Scale);
	InvertTRS(m_TRS);
}

void dae::Transform::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
}

void dae::Transform::SetPosition(const Vector& p)
{
	m_Position = p;
}

void dae::Transform::SetRotation(float angle, bool isDegree)
{
	if (isDegree)
		angle = DegToRad(angle);
	m_Rotation = angle;
}

void dae::Transform::SetScale(float x, float y)
{
	m_Scale.x = x;
	m_Scale.y = y;
}

void dae::Transform::SetScale(const Vector& s)
{
	m_Scale = s;
}
