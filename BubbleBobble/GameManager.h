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
		GameManager(GameObject* go, Player* player, CameraComponent* camera, RenderComponent* background,
			RenderComponent* cursor, RenderComponent* text1, RenderComponent* text2, RenderComponent* text3);
		~GameManager();
		//ro5
		GameManager& operator=(GameManager&&) = delete;
		GameManager& operator=(const GameManager&) = delete;
		GameManager(GameManager&&) = delete;
		GameManager(const GameManager&) = delete;

		void Update() override;
	private:
		Statemachine m_GameState;
		LevelTransitionState* m_LevelTransition;
		IngameState* m_Ingame;
		MenuState* m_Menu;
	};
}