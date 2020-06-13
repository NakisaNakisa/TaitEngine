#pragma once
#include "StateMachine.h"

namespace tait
{
	class Player;
	class Enemy;
	class IngameState : public State
	{
	public:
		IngameState(Player* player, Statemachine* fsm);

		virtual void Run() override;
		virtual void Enter() override;
		virtual void Exit() override;

		void SetEnemyInLevelAmount(int enemiesInLevel);
		void EnemyDied();
	private:
		Player* m_Player;
		Statemachine* m_FSM;
		int m_LevelId{};
		int m_EnemiesInLevel{};
		int m_DeadEnemies{};
	};
}