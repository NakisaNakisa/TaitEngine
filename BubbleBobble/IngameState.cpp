#include "TaitPCH.h"
#include "IngameState.h"
#include "Player.h"
#include "Time.h"
#include "InputManager.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "Scene.h"


tait::IngameState::IngameState(std::shared_ptr<tait::GameObject>& playerGo, Statemachine* fsm, GameManager& gm)
	: m_Player{ playerGo }
	, m_FSM{ fsm }
	, m_GM{ gm }
{
}

void tait::IngameState::Run()
{
	if (InputManager::GetInstance().IsKeyDown(SDLK_p) || InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::Start, 0))
	{
		Time::GetInstance().ToggleTime();
	}
	if (InputManager::GetInstance().IsKeyDown(SDLK_KP_PLUS))
		m_GM.LevelFinished();
}

void tait::IngameState::Enter()
{
	const int windowH{ 424 };
	++m_LevelId %= m_MaxLevelId;
	SceneManager::GetInstance().SetActiveScene(m_LevelId, false);
	m_Player->SetActiveStatus(true);
	m_Player->GetComponent<Player>()->SetActiveStatus(true);
	m_Player->GetComponent<Player>()->SetLevelStartEnd((m_LevelId - 1) * windowH, m_LevelId * windowH);
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
