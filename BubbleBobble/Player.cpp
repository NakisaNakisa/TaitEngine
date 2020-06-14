#include "TaitPCH.h"
#include "Player.h"
#include "SpriteRenderComponent.h"
#include "CharacterControllerComponent.h"
#include "GameObject.h"
#include "Projectile.h"

using namespace tait;

Player::Player(GameObject& go)
	: Component(go)
	, m_CharacterController{ go.GetComponent<CharacterControllerComponent>() }
	, m_Renderer{ go.GetComponent<SpriteRenderComponent>() }
	, m_PlayerFlag{ 0 }
	, m_AttackDuration{}
	, m_DamagedDuration{}
	, m_Bubbles{}
{
	m_AttackDuration.SetTimes(0.8f);
	m_DamagedDuration.SetTimes(1.f, 0.2f);
	m_Bubbles.resize(m_MaxBubbles);
	m_GameObject.SetTag(m_PlayerTag);
	
	for (int i = 0; i < m_MaxBubbles; i++)
	{
		CreateBubble(i);
	}
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
	if (m_Lives <= 0)
		m_PlayerFlag |= 1 << (int)PlayerFlags::IsDead;
}

void tait::Player::SetLevelStartEnd(int top, int bottom)
{
	m_LevelBottom = bottom;
	m_LevelTop = top;
}

void tait::Player::OnTriggerEnter(ColliderComponent* other)
{
	if (other->GetGameObject().IsTag(m_BubbleTag))
	{
		Projectile* p{ other->GetGameObject().GetComponent<Projectile>() };
		if (p)
			p->Pop();
		m_CharacterController->GetPhysics()->SetVelocity(Vector{ 0,0 });
		m_CharacterController->GetPhysics()->AcessAcceleration().y = m_BubbleJumpAcceleration;
	}
}

void tait::Player::Fire()
{
	if ((m_PlayerFlag & FLAG::IsShooting))) != 0)
		return;
	m_PlayerFlag |= 1 << (int)PlayerFlags::IsShooting;
	m_Renderer->SetUpdateSprite(true);
	m_Renderer->SetStartFrame(16 + 48 * m_CharacterController->GetPlayerId());
	m_AttackDuration.Activate();
	for (Projectile* bubble : m_Bubbles)
	{
		if (!bubble->IsActive())
		{
			float shootForce{ m_ShootForce };
			Vector pos{ m_GameObject.GetTransform().GetPosition() + Vector{m_GameObject.GetTransform().GetSize().x, 0} };
			if ((m_PlayerFlag & FLAG::IsMovingLeft))) != 0)
			{
				shootForce *= -1;
				pos.x -= m_GameObject.GetTransform().GetSize().x * 2;
			}
			bubble->Shoot(pos, Vector{ shootForce, 0 }, m_BubbleFriction, m_BubbleGravity, m_BubbleFloatDuration);
			bubble->SetActiveStatus(true);
			break;
		}
	}
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
		m_Renderer->SetUpdateSprite(true);
		m_PlayerFlag &= ~(1 << (int)PlayerFlags::IsMoving);
	}
	if (INPUTINST.IsKeyDown(SDLK_e) || INPUTINST.IsKeyDown(SDLK_RETURN))
		Fire();
	if (INPUTINST.IsControllerButtonPressed(ControllerButton::ButtonB, m_CharacterController->GetPlayerId()))
		Fire();
}

void tait::Player::SetRendererState()
{
	if ((m_PlayerFlag & FLAG::IsMoving))) != 0)
	{
		if ((m_PlayerFlag & FLAG::IsMovingLeft))) != 0)
			m_Renderer->SetStartFrame(WalkLeft + 48 * m_CharacterController->GetPlayerId());
		else
			m_Renderer->SetStartFrame(WalkRight + 48 * m_CharacterController->GetPlayerId());
		m_Renderer->SetAmount(WalkLeft);
		m_Renderer->SetFrameDuration(m_WalkFrameDuration);
	}
	if ((m_PlayerFlag & FLAG::IsShooting))) != 0)
	{
		if ((m_PlayerFlag & FLAG::IsMovingLeft))) != 0)
			m_Renderer->SetStartFrame(ShootLeft + 48 * m_CharacterController->GetPlayerId());
		else
			m_Renderer->SetStartFrame(ShootRight + 48 * m_CharacterController->GetPlayerId());
		m_Renderer->SetAmount(ShootRight);
		m_Renderer->SetFrameDuration(m_ShootFrameDuration);
	}
	else
	{
		if ((m_PlayerFlag & FLAG::IsMovingLeft))) != 0)
			m_Renderer->SetStartFrame(WalkLeft + 48 * m_CharacterController->GetPlayerId());
		else
			m_Renderer->SetStartFrame(WalkRight + 48 * m_CharacterController->GetPlayerId());
		m_Renderer->SetAmount(WalkLeft);
		m_Renderer->SetFrameDuration(m_WalkFrameDuration);
	}
}

void tait::Player::GapCap()
{
	if (m_GameObject.GetTransform().GetPosition().y > m_LevelBottom)
		m_GameObject.GetTransform().SetPosition(m_GameObject.GetTransform().GetPosition().x, m_LevelTop - m_GameObject.GetTransform().GetSize().y);
}

void tait::Player::CreateBubble(int i)
{
	auto bubbleGo = std::make_shared<GameObject>();
	auto col = bubbleGo->AddComponent<ColliderComponent>();
	Vector size = m_GameObject.GetTransform().GetSize();
	col->SetSize(size);
	col->SetIsTrigger(true);
	bubbleGo->AddComponent<PseudoPhysicsComponent>();
	auto sprite = bubbleGo->AddComponent<SpriteRenderComponent>();
	sprite->SetSprite("Projectile.png", 8, 12, 0.1f, 8 * 12);
	sprite->SetSize(size);
	m_Bubbles[i] = new Projectile(bubbleGo);
	m_Bubbles[i]->SetActiveStatus(false);
	bubbleGo->AddComponent(m_Bubbles[i]);
	bubbleGo->SetTag(m_BubbleTag);
	bubbleGo->GetTransform().SetPosition(-50, -50);
}
