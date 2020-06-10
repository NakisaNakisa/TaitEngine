#include "TaitPCH.h"
#include "CharacterControllerComponent.h"
#include "Time.h"
#include "GameObject.h"

tait::CharacterControllerComponent::CharacterControllerComponent(GameObject& go)
	: Component(go)
	, m_Physics{ go.GetComponent<PseudoPhysicsComponent>() }
{

}

#define MOVELEFT m_Physics->AcessAcceleration().x = -m_MoveSpeed * Time::GetInstance().GetDeltaTime()
#define MOVERIGHT m_Physics->AcessAcceleration().x = +m_MoveSpeed * Time::GetInstance().GetDeltaTime()
#define JUMP m_Physics->AcessAcceleration().y = m_JumpForce

void tait::CharacterControllerComponent::Update()
{
	Vector stick{ InputManager::GetInstance().ControllerStickValues(m_PlayerId, true) };
	if (InputManager::GetInstance().IsKeyDown(SDLK_a))
		MOVELEFT;
	else if (stick.x < 0)
		MOVELEFT;
	if (InputManager::GetInstance().IsKeyDown(SDLK_d))
		MOVERIGHT;
	else if (stick.x > 0)
		MOVERIGHT;
	if (InputManager::GetInstance().IsKeyDown(SDLK_SPACE))
	{
		if (IsGrounded())
			JUMP;
	}
	else if (InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::ButtonA, m_PlayerId))
		if (IsGrounded())
			JUMP;
}

bool tait::CharacterControllerComponent::IsGrounded()
{
	return m_Physics->IsGrounded();
}
