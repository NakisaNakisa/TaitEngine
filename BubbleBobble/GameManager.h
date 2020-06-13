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
	class GameManager : public Component
	{
	public:
		GameManager(GameObject* go, std::shared_ptr<tait::GameObject>& playerGo, CameraComponent* camera, RenderComponent* background,
			RenderComponent* cursor, RenderComponent* text1, RenderComponent* text2, RenderComponent* text3);
		~GameManager();
		//ro5
		GameManager& operator=(GameManager&&) = delete;
		GameManager& operator=(const GameManager&) = delete;
		GameManager(GameManager&&) = delete;
		GameManager(const GameManager&) = delete;

		void Update() override;
		void LevelFinished();
	private:
		const int m_MaxLevels{ 3 };
		Statemachine m_GameState;
		LevelTransitionState* m_LevelTransition;
		IngameState* m_Ingame;
		MenuState* m_Menu;
		std::shared_ptr<tait::GameObject>& m_PlayerGo;
		int m_LevelId{ 1 };

	};
}