#pragma once
#include "Component.h"
#include "StateMachine.h"

namespace tait
{
	class Player;
	class CameraComponent;
	class LevelTransitionState;
	class IngameState;
	class MenuState;
	class RenderComponent;
	class Enemy;
	class GameManager : public Component
	{
	public:
		GameManager(GameObject* go, std::shared_ptr<tait::GameObject>& playerGo, std::shared_ptr<tait::GameObject>& player2Go, CameraComponent* camera, RenderComponent* background,
			RenderComponent* cursor, RenderComponent* text1, RenderComponent* text2, RenderComponent* text3);
		~GameManager();
		//ro5
		GameManager& operator=(GameManager&&) = delete;
		GameManager& operator=(const GameManager&) = delete;
		GameManager(GameManager&&) = delete;
		GameManager(const GameManager&) = delete;

		void Update() override;
		void LevelFinished();
		void SetEnemies(std::vector<Enemy*> m_Enemies, std::vector<Vector> m_EnemyPos, std::vector<int> m_LevelEnemyAmount);
		void SetTwoPlayers();
		IngameState* GetIngameState() const { return m_Ingame; }
		void GameOver();
	private:
		const int m_MaxLevels{ 3 };
		Statemachine m_GameState;
		LevelTransitionState* m_LevelTransition;
		IngameState* m_Ingame;
		MenuState* m_Menu;
		std::shared_ptr<tait::GameObject>& m_PlayerGo;
		std::shared_ptr<tait::GameObject>& m_Player2Go;
		int m_LevelId{ 1 };
		bool m_TwoPlayers{};
	};
}