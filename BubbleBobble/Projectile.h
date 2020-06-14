#pragma once
#include "Component.h"
#include "PseudoPhysicsComponent.h"
#include "DurationTool.h"

namespace tait
{
	class SpriteRenderComponent;
	class Projectile : public Component
	{
	public:
		Projectile(std::shared_ptr<GameObject>& go);

		void Update() override;
		void SwitchMode();
		void Shoot(const Vector& startPosition, const Vector& Veclocity, float friction, float gravity, float floatDuration);
		void Pop();
		void Disappear();
		void SetPlayerId(int id) { m_PlayerId = id; }
		int GetPlayerid() const { return m_PlayerId; }
	private:
		PseudoPhysicsComponent* m_Physics;
		ColliderComponent* m_Collider;
		SpriteRenderComponent* m_Renderer;
		DurationTool m_FloatDuration{};
		DurationTool m_PopDuration{};
		float m_Gravity{};
		int m_PlayerId{};
		bool m_HasSwitched{ false };
	};
}