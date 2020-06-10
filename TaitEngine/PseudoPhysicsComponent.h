#pragma once
#include "Component.h"
#include "ColliderComponent.h"

namespace tait
{
	class PseudoPhysicsComponent : public Component
	{
	public:
		PseudoPhysicsComponent(GameObject& go, const ColliderComponent& c);

		virtual void Update() override;
		virtual void PreUpdate() override;
		virtual void PostUpdate() override;

		bool IsGrounded() const;
		Vector& AcessAcceleration();

	private:
		const ColliderComponent& m_Collider;
		ColliderComponent* m_Other;
		Vector m_Velocity;
		Vector m_Acceleration;
		float m_Gravity;
		float m_Friction;
		float m_GroundFriction;
	};
}