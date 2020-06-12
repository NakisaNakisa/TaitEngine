#pragma once
#include "Component.h"
#include "ColliderComponent.h"

namespace tait
{
	class PseudoPhysicsComponent : public Component
	{
	public:
		PseudoPhysicsComponent(GameObject& go);
		~PseudoPhysicsComponent() = default;

		PseudoPhysicsComponent(const PseudoPhysicsComponent& other) = delete;
		PseudoPhysicsComponent(PseudoPhysicsComponent&& other) = delete;
		PseudoPhysicsComponent& operator=(const PseudoPhysicsComponent& other) = delete;
		PseudoPhysicsComponent& operator=(PseudoPhysicsComponent&& other) = delete;

		virtual void Update() override;
		virtual void PreUpdate() override;
		virtual void PostUpdate() override;

		

		bool IsGrounded() const;
		Vector& AcessAcceleration();

	private:
		ColliderComponent* m_Collider;
		ColliderComponent* m_Other;
		Vector m_Velocity;
		Vector m_Acceleration;
		Vector m_MaxVelocity;
		float m_Gravity;
		float m_Friction;
		float m_GroundFriction;

		void CapVelocity();
	};
}