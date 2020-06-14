#include "TaitPCH.h"
#include "IngameState.h"
#include "Player.h"
#include "Time.h"
#include "InputManager.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "Scene.h"


tait::IngameState::IngameState(std::shared_ptr<tait::GameObject>& playerGo, std::shared_ptr<tait::GameObject>& player2Go, Statemachine* fsm, GameManager& gm)
	: m_Player{ playerGo }
	, m_Player2{ player2Go }
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
	if (m_LevelId > 0)
	{
		m_SpawnedEnemies = 0;	
		for (int i = 0; i < m_EnemiesPerLevel[m_EnemyVectorId]; i++)
		{
			m_EnemySpawnId++;
			m_Enemies[m_EnemySpawnId]->GetGameObject().GetTransform().SetPosition(m_EnemieSpawnPos[m_EnemySpawnId] + Vector{ 0,424.f * m_EnemyVectorId });
			m_Enemies[m_EnemySpawnId]->GetGameObject().SetActiveStatus(true);
		}
		m_EnemyVectorId++;
	}
	m_Player->SetActiveStatus(true);
	m_Player->GetComponent<Player>()->SetActiveStatus(true);
	m_Player->GetComponent<Player>()->SetLevelStartEnd((m_LevelId - 1) * windowH, m_LevelId * windowH);
	if (m_TwoPlayers)
	{
		m_Player2->SetActiveStatus(true);
		m_Player2->GetComponent<Player>()->SetActiveStatus(true);
		m_Player2->GetComponent<Player>()->SetLevelStartEnd((m_LevelId - 1) * windowH, m_LevelId * windowH);
	}
}

void tait::IngameState::Exit()
{
}

void tait::IngameState::SetEnemies(std::vector<Enemy*> enemies, std::vector<Vector> enemyPos, std::vector<int> levelEnemyAmount)
{
	m_Enemies = enemies;
	m_EnemieSpawnPos = enemyPos;
	m_EnemiesPerLevel = levelEnemyAmount;
}

void tait::IngameState::EnemyDied()
{
	m_DeadEnemies++;
	if (m_DeadEnemies >= m_EnemiesInLevel)
	{
		m_FSM->Transition();
	}
}
