#pragma once
#include "Component.h"
#include "DurationTool.h"

namespace tait
{
	class SpriteRenderComponent;
	class ColliderComponent;
	class PseudoPhysicsComponent;
	class Player;
	class Projectile;

	class Enemy : public Component
	{
	public:
		Enemy(GameObject& go, int type);
		
		void OnTriggerEnter(ColliderComponent* other) override;

		void Update() override;
		void BubbleUp(bool byGreen);
		void Pop();
		bool IsInBubble() const { return m_IsInBubble; }
		void GivePlayer(Player* player1, Player* player2 = nullptr);
		void SetTopBottom(float top, float bottom);
	private:
		const int m_MoveLeft{ 0 };
		const int m_MoveRight{ 8 };
		const int m_InGreenBubble{ 16 };
		const int m_InBlueBubble{ 24 };
		const int m_TypeOffset{ 32 };
		const float m_FloatTime{ 4.f };
		const float m_FloatGravity{ -2.7f };
		const float m_WalkSpeed{ 40 };
		const float m_SprintSpeed{ 100 };
		const float m_ShootForce{ 150 };
		const float m_BolderFriction{ 90 };

		SpriteRenderComponent* m_Renderer;
		ColliderComponent* m_Collider;
		PseudoPhysicsComponent* m_Physics;
		DurationTool m_FloatingDuration{};
		DurationTool m_ShootingCooldown{};
		Rect m_ViewRect{};
		Player* m_Player1;
		Player* m_Player2;
		Projectile* m_Projectile;
		int m_Type;
		float m_LevelBottom;
		float m_LevelTop;
		bool m_IsInBubble{}, m_IsLookingleft{ true }, m_IsInGreenBubble{};

		void ChangeDirection();
		void SharedUpdate();
		void Enemy1Update();
		void Enemy2Update();
		void GapCap();
	};
}