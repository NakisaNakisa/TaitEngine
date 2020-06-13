#pragma once
#include "Component.h"
#include "Command.h"
#include "PseudoPhysicsComponent.h"


namespace tait
{
	class CharacterControllerComponent final : public Component
	{
	public:
		explicit CharacterControllerComponent(GameObject& go);
		virtual ~CharacterControllerComponent() = default;
		CharacterControllerComponent(const CharacterControllerComponent& other) = delete;
		CharacterControllerComponent(CharacterControllerComponent&& other) = delete;
		CharacterControllerComponent& operator=(const CharacterControllerComponent& other) = delete;
		CharacterControllerComponent& operator=(CharacterControllerComponent&& other) = delete;

		virtual void Update() override;

		int GetPlayerId() const { return m_PlayerId; }
		PseudoPhysicsComponent* GetPhysics() const { return m_Physics; }
		float GetJumpForce() const { return m_JumpForce; }
		float GetMoveSpeed() const { return m_MoveSpeed; }

		void SetMoveSpeed(float moveSpeed) { m_MoveSpeed = moveSpeed; }
		void SetJumpForce(float jumpForce) { m_JumpForce = jumpForce; }


		bool IsGrounded();
	private:
		static int m_PlayerAmount;
		PseudoPhysicsComponent* m_Physics;
		float m_MoveSpeed{ 20 };
		float m_JumpForce{ 300 };
		int m_PlayerId{};
	};
}
