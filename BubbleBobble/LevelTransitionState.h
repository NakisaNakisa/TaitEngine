#pragma once
#include "StateMachine.h"
#include "Scene.h"
namespace tait
{
	class Player;
	class CameraComponent;
	class LevelTransitionState : public tait::State
	{
	public:
		LevelTransitionState(Player* player, CameraComponent* camera, Statemachine* fsm);
		
		void SetOldScene(Scene* oldScene);

		virtual void Run() override;
		virtual void Enter() override;
		virtual void Exit() override;
	private:
		const float m_DistanceToMove{ 512 };
		const float m_CameraSpeed{ m_DistanceToMove / 5.f };
		const Vector m_PlayerTarget{ 50, 360 };

		Player* m_Player;
		CameraComponent* m_Camera;
		Statemachine* m_FSM;
		Scene* m_OldScene;
		float m_MovedDistance{};
		Vector m_PlayerMoveSpeed{}; 
		
		int m_MaxLevels{};
		int m_CurrentLevelId{};
	};
}