#pragma once
#include "Component.h"
#include "DurationTool.h"

namespace tait
{
	class SpriteRenderComponent;
	class ColliderComponent;
	class PseudoPhysicsComponent;

	class Enemy : public Component
	{
	public:
		Enemy(GameObject& go, int type);
		
		void OnTriggerEnter(ColliderComponent* other) override;

		void Update() override;
		void BubbleUp(bool byGreen);
		void Pop();
	private:
		const int m_MoveLeft{ 0 };
		const int m_MoveRight{ 8 };
		const int m_InGreenBubble{ 16 };
		const int m_InBlueBubble{ 24 };
		const int m_TypeOffset{ 32 };
		const float m_FloatTime{ 4.f };
		const float m_FloatGravity{ -2.7f };

		SpriteRenderComponent* m_Renderer;
		ColliderComponent* m_Collider;
		PseudoPhysicsComponent* m_Physics;
		DurationTool m_FloatingDuration{};
		int m_Type;
		bool m_IsInBubble{}, m_IsLookingleft{ true }, m_IsInGreenBubble{};

		void Enemy1Update();
		void Enemy2Update();
	};
}