#include "TaitPCH.h"
#include "CharacterControllerComponent.h"
#include "Time.h"
#include "GameObject.h"

int tait::CharacterControllerComponent::m_PlayerAmount{ 0 };

tait::CharacterControllerComponent::CharacterControllerComponent(GameObject& go)
	: Component(go)
	, m_Physics{ go.GetComponent<PseudoPhysicsComponent>() }
{
	if (!m_Physics)
		m_Physics = m_GameObject.AddComponent<PseudoPhysicsComponent>();
	m_PlayerId = m_PlayerAmount;
	m_PlayerAmount++;
}

#define MOVELEFT m_Physics->AcessAcceleration().x = -m_MoveSpeed//; std::cout << m_Physics->AcessAcceleration().x << std::endl
#define MOVERIGHT m_Physics->AcessAcceleration().x = +m_MoveSpeed//; std::cout << m_Physics->AcessAcceleration().x << std::endl
#define JUMP m_Physics->AcessAcceleration().y = -m_JumpForce//; std::cout << m_Physics->AcessAcceleration().y << std::endl

void tait::CharacterControllerComponent::Update()
{
	Vector stick{ InputManager::GetInstance().ControllerStickValues(m_PlayerId, true) };
	if (InputManager::GetInstance().IsKeyPressed(SDLK_a))
	{
		MOVELEFT;
	}
	else if (stick.x < 0)
	{
		MOVELEFT;
	}
	if (InputManager::GetInstance().IsKeyPressed(SDLK_d))
	{
		MOVERIGHT;
	}
	else if (stick.x > 0)
	{
		MOVERIGHT;
	}
	if (InputManager::GetInstance().IsKeyPressed(SDLK_SPACE))
	{
		if (IsGrounded())
		{
			JUMP;
		}
	}
	else if (InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::ButtonA, m_PlayerId))
	{
		if (IsGrounded())
		{
			JUMP;
		}
	}
}

bool tait::CharacterControllerComponent::IsGrounded()
{
	return m_Physics->IsGrounded();
}
