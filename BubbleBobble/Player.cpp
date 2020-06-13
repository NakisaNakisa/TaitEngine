#include "TaitPCH.h"
#include "Player.h"
#include "SpriteRenderComponent.h"
#include "CharacterControllerComponent.h"
#include "GameObject.h"

using namespace tait;

Player::Player(GameObject& go)
	: Component(go)
	, m_CharacterController{ go.GetComponent<CharacterControllerComponent>() }
	, m_Renderer{ go.GetComponent<SpriteRenderComponent>() }
	, m_PlayerFlag{0}
	, m_AttackDuration{}
	, m_DamagedDuration{}
{
	m_AttackDuration.SetTimes(0.8f);
	m_DamagedDuration.SetTimes(1.f, 0.2f);
}

#define INPUTINST InputManager::GetInstance()

void tait::Player::Update()
{
	Ticks();
	Input();
	SetRendererState();
	GapCap();
}

#define FLAG (DWORD)pow(DWORD(2), DWORD(PlayerFlags

void tait::Player::Damage()
{
	if ((m_PlayerFlag & FLAG::IsDamaged))) != 0)
		return;
	m_Lives--;
	m_PlayerFlag |= 1 << (int)PlayerFlags::IsDamaged;
	m_DamagedDuration.Activate();
	if(m_Lives <= 0)
		m_PlayerFlag |= 1 << (int)PlayerFlags::IsDead;
}

void tait::Player::SetLevelStartEnd(int top, int bottom)
{
	m_LevelBottom = bottom;
	m_LevelTop = top;
}

void tait::Player::Fire()
{
	if ((m_PlayerFlag & FLAG::IsShooting))) != 0)
		return;
	m_PlayerFlag |= 1 << (int)PlayerFlags::IsShooting;
	m_Renderer->SetUpdateSprite(true);
	m_Renderer->SetStartFrame(16);
	m_AttackDuration.Activate();
}

void tait::Player::Ticks()
{
	if (m_AttackDuration.IsActive())
	{
		m_AttackDuration.Tick();
		if (!m_AttackDuration.IsActive())
			m_PlayerFlag &= ~(1 << (int)PlayerFlags::IsShooting);
	}
	if (m_DamagedDuration.IsActive())
	{
		if (m_DamagedDuration.Tick())
			m_Renderer->SetActiveStatus(!m_Renderer->GetActiveStatus());
		if (!m_DamagedDuration.IsActive())
		{
			m_PlayerFlag &= ~(1 << (int)PlayerFlags::IsDamaged);
			m_Renderer->SetActiveStatus(true);
		}
	}
}

void tait::Player::Input()
{
	Vector stick{ INPUTINST.ControllerStickValues(m_CharacterController->GetPlayerId(), true) };
	if (INPUTINST.IsKeyDown(SDLK_a))
	{
		m_PlayerFlag |= 1 << (int)PlayerFlags::IsMovingLeft;
		m_PlayerFlag |= 1 << (int)PlayerFlags::IsMoving;
		m_Renderer->SetUpdateSprite(true);
	}
	else if (stick.x < 0)
	{
		m_PlayerFlag |= 1 << (int)PlayerFlags::IsMovingLeft;
		m_PlayerFlag |= 1 << (int)PlayerFlags::IsMoving;
		m_Renderer->SetUpdateSprite(true);
	}
	else if (INPUTINST.IsKeyDown(SDLK_d))
	{
		m_PlayerFlag &= ~(1 << (int)PlayerFlags::IsMovingLeft);
		m_PlayerFlag |= 1 << (int)PlayerFlags::IsMoving;
		m_Renderer->SetUpdateSprite(true);
	}
	else if (stick.x > 0)
	{
		m_PlayerFlag &= ~(1 << (int)PlayerFlags::IsMovingLeft);
		m_PlayerFlag |= 1 << (int)PlayerFlags::IsMoving;
		m_Renderer->SetUpdateSprite(true);
	}
	else
	{
		//m_Renderer->SetUpdateSprite(false);
		m_PlayerFlag &= ~(1 << (int)PlayerFlags::IsMoving);
	}
	if (INPUTINST.IsKeyDown(SDLK_e) || INPUTINST.IsKeyDown(SDLK_RETURN))
		Fire();
}

void tait::Player::SetRendererState()
{
	if ((m_PlayerFlag & FLAG::IsMoving))) != 0)
	{
		if ((m_PlayerFlag & FLAG::IsMovingLeft))) != 0)
			m_Renderer->SetStartFrame(WalkLeft);
		else
			m_Renderer->SetStartFrame(WalkRight);
		m_Renderer->SetAmount(WalkLeft);
		m_Renderer->SetFrameDuration(m_WalkFrameDuration);
	}
	if ((m_PlayerFlag & FLAG::IsShooting))) != 0)
	{
		if ((m_PlayerFlag & FLAG::IsMovingLeft))) != 0)
			m_Renderer->SetStartFrame(ShootLeft);
		else
			m_Renderer->SetStartFrame(ShootRight);
		m_Renderer->SetAmount(ShootRight);
		m_Renderer->SetFrameDuration(m_ShootFrameDuration);
	}
	else
	{
		if ((m_PlayerFlag & FLAG::IsMovingLeft))) != 0)
			m_Renderer->SetStartFrame(WalkLeft);
		else
			m_Renderer->SetStartFrame(WalkRight);
		m_Renderer->SetAmount(WalkLeft);
		m_Renderer->SetFrameDuration(m_WalkFrameDuration);
	}
}

void tait::Player::GapCap()
{
	if (m_GameObject.GetTransform().GetPosition().y > m_LevelBottom)
		m_GameObject.GetTransform().SetPosition(m_GameObject.GetTransform().GetPosition().x, m_LevelTop - m_GameObject.GetTransform().GetSize().y);
}
