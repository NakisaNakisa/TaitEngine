#include "TaitPCH.h"
#include "LevelTransitionState.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "Player.h"
#include "CharacterControllerComponent.h"

tait::LevelTransitionState::LevelTransitionState(Player* player, CameraComponent* camera, Statemachine* fsm)
	: m_Camera{ camera }
	, m_Player{ player }
	, m_FSM{ fsm }
	, m_OldScene{ nullptr }
{

}

void tait::LevelTransitionState::SetOldScene(Scene* oldScene)
{
	m_OldScene = oldScene;
}

void tait::LevelTransitionState::Run()
{
	float dt = Time::GetInstance().GetDeltaTime();
	float d = dt * m_CameraSpeed;
	m_MovedDistance += d;
	m_Camera->GetGameObject().GetTransform().Translate(Vector{ 0, d });
	m_Player->GetGameObject().GetTransform().Translate(m_PlayerMoveSpeed * dt);
	if (m_MovedDistance >= m_DistanceToMove)
	{
		float dBack = m_MovedDistance - m_DistanceToMove;
		m_Camera->GetGameObject().GetTransform().Translate(Vector{ 0, dBack });
		m_FSM->Transition();
	}
}

void tait::LevelTransitionState::Enter()
{
	m_MovedDistance = 0;
	m_Player->GetCharacterController()->GetPhysics()->SetActiveStatus(false);
	m_Player->GetCharacterController()->SetActiveStatus(false);
	m_Player->SetActiveStatus(false);
	m_PlayerMoveSpeed = (m_PlayerTarget - m_Player->GetGameObject().GetTransform().GetPosition()) / 5.f;
}

void tait::LevelTransitionState::Exit()
{
	m_Player->SetActiveStatus(true);
	m_Player->GetCharacterController()->SetActiveStatus(true);
	m_Player->GetCharacterController()->GetPhysics()->SetActiveStatus(true);
	m_OldScene->Activate(false);
}
