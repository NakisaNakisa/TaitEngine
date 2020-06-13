#include "TaitPCH.h"
#include "IngameState.h"
#include "Player.h"
#include "Time.h"
#include "InputManager.h"
#include "Enemy.h"

tait::IngameState::IngameState(Player* player, Statemachine* fsm)
	: m_Player{ player }
	, m_FSM{ fsm }
{
}

void tait::IngameState::Run()
{
	if (InputManager::GetInstance().IsKeyDown(SDLK_p) || InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::Start, 0))
	{
		Time::GetInstance().ToggleTime();
	}
}

void tait::IngameState::Enter()
{
	
}

void tait::IngameState::Exit()
{
}

void tait::IngameState::SetEnemyInLevelAmount(int enemiesInLevel)
{
	m_EnemiesInLevel = enemiesInLevel;
	m_DeadEnemies = 0;
}

void tait::IngameState::EnemyDied()
{
	m_DeadEnemies++;
	if (m_DeadEnemies >= m_EnemiesInLevel)
	{
		m_FSM->Transition();
	}
}
