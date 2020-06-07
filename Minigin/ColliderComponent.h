#pragma once
#include "Component.h"

namespace tait
{
	class ColliderComponent : public Component
	{
	public:
		ColliderComponent(GameObject& go);

		void SetPos(const Vector& p);
		void SetSize(const Vector& s);
		void SetRect(const Rect& r);
		void SetIsTrigger(bool isTrigger) { m_IsTrigger = isTrigger; }
		
		bool IsTrigger() const { return m_IsTrigger; }
		bool IsColliding(const Vector& start, const Vector& end, Vector& hit);
	private:
		Rect m_Coords;
		bool m_IsTrigger;
		bool m_IsColliding = false;

		void CollisionIsOccuring(bool isColliding);
	};
}