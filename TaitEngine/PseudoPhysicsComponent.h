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

		const Vector& GetVelocity() const { return m_Velocity; }
		const Vector& GetMaxVelocity() const { return m_MaxVelocity; }
		float GetGravity() const { return m_Gravity; }
		float GetFriction() const { return m_Friction; }

		void SetMaxVelocity(const Vector& vel) { m_MaxVelocity = vel; }
		void SetGravity(float grav) { m_Gravity = grav; }
		void SetFriction(float fric) { m_Friction = fric; }
		void SetVelocity(const Vector& vel) { m_Velocity = vel; }

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

		void CapVelocity();
	};
}