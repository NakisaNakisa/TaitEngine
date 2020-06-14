#include "TaitPCH.h"
#include "MenuState.h"
#include "InputManager.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "GameObject.h"
#include "CameraComponent.h"
#include "GameManager.h"

tait::MenuState::MenuState
(
	CameraComponent* camera, Statemachine* fsm, RenderComponent* background,
	RenderComponent* cursor, RenderComponent* text1, RenderComponent* text2, RenderComponent* text3,
	GameManager* gm
)
	: m_Camera{ camera }
	, m_FSM{ fsm }
	, m_Background{ background }
	, m_Cursor{ cursor }
	, m_Text1{ text1 }
	, m_Text2{ text2 }
	, m_Text3{ text3 }
	, m_GM{ gm }
{
	m_MoveSpeed = m_DistanceToMove / m_TransitionTimeInSeconds;
	m_InputCooldown.SetTimes(0.2f);
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
	m_MovedDistance = 0;
	m_Camera->GetGameObject().GetTransform().SetPosition(0, 0);
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
	m_CurrentState = MenuStates::TitleCard;
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
		|| InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::ButtonA, 0))
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
		if (InputManager::GetInstance().IsKeyDown(SDLK_UP) || InputManager::GetInstance().IsKeyDown(SDLK_w))
		{
			MoveUp();
		}
		else if (InputManager::GetInstance().IsKeyDown(SDLK_DOWN) || InputManager::GetInstance().IsKeyDown(SDLK_s))
		{
			MoveDown();
		}
		if (!m_InputCooldown.IsActive())
		{
			if (InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::DPadDown, 0))
			{
				MoveDown();
				m_InputCooldown.Activate();
			}
			else if (InputManager::GetInstance().IsControllerButtonPressed(ControllerButton::DPadUp, 0))
			{	
				MoveUp();
				m_InputCooldown.Activate();
			}
			float y = InputManager::GetInstance().ControllerStickValues(0, true).y;
			if (y > 0)
			{
				MoveUp();
				m_InputCooldown.Activate();
			}
			else if (y < 0)
			{
				MoveDown();
				m_InputCooldown.Activate();
			}
		}
		else
		{
			m_InputCooldown.Tick();
		}
		if (InputManager::GetInstance().IsKeyDown(SDLK_SPACE)
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
				m_GM->SetTwoPlayers();
				m_FSM->Transition();
				break;
			case tait::MenuState::MenuStates::PvP:
				break;
			default:
				break;
			}
		}
	}
}

void tait::MenuState::MoveUp()
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

void tait::MenuState::MoveDown()
{
	int c = (int)m_CurrentState - 1;
	++c %= 3;
	c += 1;
	m_CurrentState = (MenuStates)c;
	m_Cursor->SetPosition(m_StartPos + Vector{ 0, m_OffSet * (c - 1) });
}
