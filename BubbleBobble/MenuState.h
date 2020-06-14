#pragma once
#include "StateMachine.h"
#include "DurationTool.h"

namespace tait
{
	class Player;
	class RenderComponent;
	class CameraComponent;
	class GameManager;
	class MenuState : public State
	{
		enum class MenuStates
		{
			TitleCard,
			SinglePlayer,
			Coop,
			PvP
		};
	public:
		MenuState(CameraComponent* camera, Statemachine* fsm, RenderComponent* background, RenderComponent* cursor, RenderComponent* text1, RenderComponent* text2, RenderComponent* text3, GameManager* gm);

		virtual void Run() override;
		virtual void Enter() override;
		virtual void Exit() override;

	private:
		const Vector m_StartPos{ 512 / 3.f - 512 / 10.f, 424 / 5.f };
		const float m_DistanceToMove{ 424 };
		const float m_TransitionTimeInSeconds{ 3.f };
		Statemachine* m_FSM;
		RenderComponent* m_Background;
		RenderComponent* m_Cursor;
		RenderComponent* m_Text1;
		RenderComponent* m_Text2;
		RenderComponent* m_Text3;
		CameraComponent* m_Camera;
		GameManager* m_GM;
		MenuStates m_CurrentState{ MenuStates::TitleCard };
		DurationTool m_InputCooldown{};
		float m_OffSet{ m_StartPos.y };
		float m_MovedDistance{};
		float m_MoveSpeed{};
		bool m_MoveBackground{ false };

		void MoveBackground();
		void TitleCardinput();
		void MenuInput();
		void MoveUp();
		void MoveDown();
	};
}
