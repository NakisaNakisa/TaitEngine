#pragma once
#include "Component.h"
#include "Transform.h"

namespace tait
{
	class ColliderComponent : public Component
	{
		enum Flag
		{
			Trigger = 1,
			IsColliding = 2,
			IgnoreUpvelocity = 4,
			IgnoreDownVelocity = 8,
			IgnoreRightVelocity = 16,
			IgnoreLeftVelocity = 32
		};
	public:
		ColliderComponent(GameObject& go);

		void SetPos(const Vector& p);
		void SetSize(const Vector& s);
		void SetRect(const Rect& r);
		void SetIsTrigger(bool isTrigger);
		void SetIgnoreUp(bool ignore);
		void SetIgnoreDown(bool ignore);
		void SetIgnoreRight(bool ignore);
		void SetIgnoreLeft(bool ignore);
		void SetStatic(bool isStatic);

		bool IgnoreCollision(const Vector& dir);
		void MoveBack(Transform& other, Vector& velocity);

		const Rect& GetCoords() const { return m_Coords; }
		bool GetFlag() const { return m_Flag; }
		
		bool IsTrigger() const { return (m_Flag & (bool)Flag::Trigger) != 0; }

		void Update() override;
	private:
		Rect m_Coords;
		DWORD m_Flag{};
		bool m_IsStatic{ true };
	};
}