#include "TaitPCH.h"
#include "MenuState.h"
#include "InputManager.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "GameObject.h"

tait::MenuState::MenuState
(
	Player* player, Statemachine* fsm, RenderComponent* background,
	RenderComponent* cursor, RenderComponent* text1, RenderComponent* text2, RenderComponent* text3
)
	: m_Player{ player }
	, m_FSM{ fsm }
	, m_Background{ background }
	, m_Cursor{ cursor }
	, m_Text1{ text1 }
	, m_Text2{ text2 }
	, m_Text3{ text3 }
{
	m_MoveSpeed = m_DistanceToMove / 5.f;
}

void tait::MenuState::Run()
{
	MoveBackground();
	if (m_CurrentState == MenuStates::TitleCard)
		TitleCardinput();
	else
		MenuInput();
}

void tait::MenuState::Enter()
{
	m_Text1->SetActiveStatus(false);
	m_Text2->SetActiveStatus(false);
	m_Text3->SetActiveStatus(false);
	m_Cursor->GetGameObject().GetTransform().SetPosition(m_StartPos);
	m_Cursor->SetActiveStatus(false);
	m_Cursor->SetSize(Vector{ 32, 32 });
	Rect r{ m_Cursor->GetGameObject().GetTransform().GetRect() };
	r.w += m_Cursor->GetSize().x;
	r.h += m_Cursor->GetSize().y;
	m_Cursor->SetDestRect(r);
	m_Background->SetActiveStatus(true);
	m_Background->GetGameObject().GetTransform().SetPosition(Vector{ 0,0 });
	m_Cursor->SetActiveStatus(false);
}

void tait::MenuState::Exit()
{
	m_Background->SetActiveStatus(false);
	m_Cursor->SetActiveStatus(false);
	m_Text1->SetActiveStatus(false);
	m_Text2->SetActiveStatus(false);
	m_Text3->SetActiveStatus(false);
}

void tait::MenuState::MoveBackground()
{
	if (m_MoveBackground)
	{
		float d = -m_MoveSpeed * Time::GetInstance().GetDeltaTime();
		m_Background->GetGameObject().GetTransform().Translate(Vector{ 0, d });
		m_MovedDistance -= d;
		if (m_MovedDistance > m_DistanceToMove)
			m_MoveBackground = false;
	}
}

void tait::MenuState::TitleCardinput()
{
	if (InputManager::GetInstance().IsKeyDown(SDLK_SPACE)
		|| InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::Start, 0))
	{
		m_CurrentState = MenuStates::SinglePlayer;
		m_Cursor->SetActiveStatus(true);
		m_MoveBackground = true;
		m_Text1->SetActiveStatus(true);
		m_Text2->SetActiveStatus(true);
		m_Text3->SetActiveStatus(true);
	}
}

void tait::MenuState::MenuInput()
{
	if (!m_MoveBackground)
	{
		if (InputManager::GetInstance().IsKeyDown(SDLK_UP)
			|| InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::DPadUp, 0))
		{
			int c = (int)m_CurrentState - 1;
			if (c == 0)
				c = 2;
			else
				c--;
			c += 1;
			m_CurrentState = (MenuStates)c;
			m_Cursor->SetPosition(m_StartPos + Vector{ 0, m_OffSet * (c - 1) });
		}
		else if (InputManager::GetInstance().IsKeyDown(SDLK_DOWN)
			|| InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::DPadDown, 0))
		{
			int c = (int)m_CurrentState - 1;
			++c %= 3;
			c += 1;
			m_CurrentState = (MenuStates)c;
			m_Cursor->SetPosition(m_StartPos + Vector{ 0, m_OffSet * (c - 1) });
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_RETURN)
			|| InputManager::GetInstance().IsKeyDown(SDLK_SPACE)
			|| InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::Start, 0)
			|| InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::ButtonA, 0))
		{
			//start correct game mode
			std::cout << "Starting game mode " << (int)m_CurrentState << std::endl;
			switch (m_CurrentState)
			{
			case tait::MenuState::MenuStates::SinglePlayer:
				m_FSM->Transition();
				break;
			case tait::MenuState::MenuStates::Coop:
				break;
			case tait::MenuState::MenuStates::PvP:
				break;
			default:
				break;
			}
		}
		//todo support stick
	}
}
