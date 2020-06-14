#pragma once
#include "Component.h"
#include "DurationTool.h"

namespace tait
{
	class SpriteRenderComponent;
	class CharacterControllerComponent;
	class Projectile;
	
	class Player : public Component
	{
		enum SpriteStartPositions
		{
			WalkRight = 0,
			WalkLeft = 8,
			ShootRight = 16,
			ShootLeft = 32
		};
		enum class PlayerFlags
		{
			IsPlayerOne,
			IsMovingLeft,
			IsMoving,
			IsShooting,
			IsDamaged,
			IsPvp,
			IsDead
		};
	public:
		Player(GameObject& go);

		void Update() override;
		void Damage();
		void SetLevelStartEnd(int top, int bottom);
		void OnTriggerEnter(ColliderComponent* other) override;

		SpriteRenderComponent* GetSpriteRenderer() const { return m_Renderer; }
		CharacterControllerComponent* GetCharacterController() const { return m_CharacterController; }
	private:
		const float m_WalkFrameDuration{ 0.2f };
		const float m_ShootFrameDuration{ 0.1f };
		const int m_MaxBubbles{ 7 };
		const int m_BubbleTag{ 1 };
		const int m_PlayerTag{ 2 };
		const float m_BubbleJumpAcceleration{ -70 };

		std::vector<Projectile*> m_Bubbles;
		SpriteRenderComponent* m_Renderer;
		CharacterControllerComponent* m_CharacterController;
		DurationTool m_AttackDuration, m_DamagedDuration;
		DWORD m_PlayerFlag;
		int m_Lives{ 4 };
		int m_LevelTop{}, m_LevelBottom{};
		float m_ShootForce{ 150 };
		float m_BubbleFriction{ 90 };
		float m_BubbleGravity{ -10 };
		float m_BubbleFloatDuration{ 4 };

		void Fire();
		void Ticks();
		void Input();
		void SetRendererState();
		void GapCap();
		void CreateBubble(int i);
	};
}