#pragma once
#include "StateMachine.h"
#include "GameObject.h"
#include "GameManager.h"
#include "DurationTool.h"

namespace tait
{
	class Player;
	class Enemy;
	class IngameState : public State
	{
	public:
		IngameState(std::shared_ptr<tait::GameObject>& playerGo, std::shared_ptr<tait::GameObject>& player2Go, Statemachine* fsm, GameManager& gm);

		virtual void Run() override;
		virtual void Enter() override;
		virtual void Exit() override;
		void SetTwoPlayers(bool twoPlayers) { m_TwoPlayers = twoPlayers; }
		bool& IsTwoPlayers() { return m_TwoPlayers; }
		void GameOver();
		void LevelFinished();
		void SetEnemies(std::vector<Enemy*> enemies, std::vector<Vector> enemyPos, std::vector<int> levelEnemyAmount);
		void EnemyDied();
	private:
		const int m_MaxLevelId{ 4 };
		std::shared_ptr<tait::GameObject>& m_Player;
		std::shared_ptr<tait::GameObject>& m_Player2;
		Statemachine* m_FSM;
		GameManager& m_GM;
		std::vector<Enemy*> m_Enemies;
		std::vector<Vector> m_EnemieSpawnPos;
		std::vector<int> m_EnemiesPerLevel;
		int m_SpawnedEnemies{};
		int m_EnemyVectorId{};
		int m_EnemySpawnId{ -1 };
		int m_LevelId{ -1 };
		int m_EnemiesInLevel{};
		int m_DeadEnemies{};
		bool m_TwoPlayers{ false };
	};
}