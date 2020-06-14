#include "TaitPCH.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Projectile.h"
#include "EventSystem.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Player.h"

tait::Enemy::Enemy(GameObject& go, int type)
	: Component(go)
	, m_Collider{ go.GetComponent<ColliderComponent>() }
	, m_Physics{ go.GetComponent<PseudoPhysicsComponent>() }
	, m_Renderer{ go.GetComponent<SpriteRenderComponent>() }
	, m_Type{ type }
{
	m_FloatingDuration.SetTimes(m_FloatTime);
	m_ViewRect.w = m_GameObject.GetTransform().GetSize().x * 3;
	m_ViewRect.h = m_GameObject.GetTransform().GetSize().x;
	m_ShootingCooldown.SetTimes(1.f);
	if (m_Type != 1)
	{
		auto projgo = std::make_shared<GameObject>();
		auto col = projgo->AddComponent<ColliderComponent>();
		col->SetSize(m_GameObject.GetTransform().GetSize());
		col->SetStatic(false);
		col->SetIsTrigger(true);
		projgo->AddComponent<PseudoPhysicsComponent>();
		auto ren = projgo->AddComponent<SpriteRenderComponent>();
		ren->SetSprite("Projectile.png", 8, 12, 0.1f, 8 * 12);
		ren->SetSize(m_GameObject.GetTransform().GetSize());
		m_Projectile = new Projectile(projgo);
		m_Projectile->SetActiveStatus(false);
		m_Projectile->IsNotBubble();
		
		projgo->AddComponent(m_Projectile);
		projgo->SetTag(4);
		projgo->GetTransform().SetPosition(-50, -50);
	}
}

void tait::Enemy::OnTriggerEnter(ColliderComponent* other)
{
	if (other->GetGameObject().IsTag(1))
	{
		Projectile* p{ other->GetGameObject().GetComponent<Projectile>() };
		p->Disappear();
		BubbleUp(p->GetPlayerid() == 0);
	}
}

void tait::Enemy::Update()
{
	if(m_GameObject.GetTransform().GetPosition().x < 0)
		m_GameObject.SetActiveStatus(false);
	if (!m_IsInBubble)
	{
		bool isLookingLeft = m_Physics->GetVelocity().x > 0;
		if (isLookingLeft != m_IsLookingleft)
		{
			m_IsLookingleft = isLookingLeft;
			int moveStart{ m_IsLookingleft ? m_MoveLeft : m_MoveRight };
			m_Renderer->SetStartFrame(moveStart + m_TypeOffset * m_Type);
		}
		SharedUpdate();
		if (m_Type == 1)
			Enemy1Update();
		else
			Enemy2Update();
	}
	else
	{
		m_FloatingDuration.Tick();
		m_Physics->AcessAcceleration().y = m_FloatGravity;
		if (!m_FloatingDuration.IsActive())
		{
			m_Physics->SetVelocity(Vector{ 0,0 });
			m_IsInBubble = false;
		}
	}
	GapCap();
}

void tait::Enemy::BubbleUp(bool byGreen)
{
	m_IsInBubble = true;
	int bubble = byGreen ? m_InGreenBubble : m_InBlueBubble;
	m_IsInGreenBubble = byGreen;
	m_Renderer->SetStartFrame(bubble + m_Type * m_TypeOffset);
	m_Physics->SetVelocity(Vector{});
	m_FloatingDuration.Activate();
}

void tait::Enemy::Pop()
{
	m_GameObject.GetTransform().SetPosition(-50, -50);
	SceneManager::GetInstance().GetActiveScene().RemoveCollider(m_Collider);
	EventSystem::TriggerEvent(*this, Event::ENEMY_DIED);
}

void tait::Enemy::GivePlayer(Player* player1, Player* player2)
{
	m_Player1 = player1;
	m_Player2 = player2;
}

void tait::Enemy::SetTopBottom(float top, float bottom)
{
	m_LevelTop = top;
	m_LevelBottom = bottom;
}

void tait::Enemy::ChangeDirection()
{
	Vector p{};
	p = m_GameObject.GetTransform().GetCenter();
	p.x -= m_IsLookingleft ? m_GameObject.GetTransform().GetSize().x : -m_GameObject.GetTransform().GetSize().x;
	auto colliders = SceneManager::GetInstance().GetActiveScene().GetSceneColliders();
	for (auto& col : colliders)
	{
		if (IsPointInRect(col->GetCoords(), p))
		{
			m_IsLookingleft = !m_IsLookingleft;
			break;
		}
	}
}

void tait::Enemy::SharedUpdate()
{
	ChangeDirection();
	m_ViewRect.y = m_GameObject.GetTransform().GetPosition().y;
	if (m_IsLookingleft)
		m_ViewRect.x = m_GameObject.GetTransform().GetPosition().x - m_ViewRect.w - m_GameObject.GetTransform().GetSize().x;
	else
		m_ViewRect.x = m_GameObject.GetTransform().GetPosition().x;
}

void tait::Enemy::Enemy1Update()
{
	int dir{ 1 };
	if (m_IsLookingleft)
		dir = -1;
	if(m_Player1)
		if (AreRectOverlapping(m_ViewRect, m_Player1->GetGameObject().GetTransform().GetRect()))
			m_Physics->AcessAcceleration().x = m_SprintSpeed * dir;
	else if(m_Player2)
		if (AreRectOverlapping(m_ViewRect, m_Player2->GetGameObject().GetTransform().GetRect()))
			m_Physics->AcessAcceleration().x = m_SprintSpeed * dir;
	else
		m_Physics->AcessAcceleration().x = m_WalkSpeed * dir;
}

void tait::Enemy::Enemy2Update()
{
	int dir{ 1 };
	Vector pos{ m_GameObject.GetTransform().GetPosition() + Vector{m_GameObject.GetTransform().GetSize().x, 0} };
	if (m_IsLookingleft)
	{
		dir = -1;
		pos.x -= m_GameObject.GetTransform().GetSize().x * 2;
	}
	if (!m_ShootingCooldown.IsActive())
	{
		if (!m_Projectile->IsActive())
		{
			if (m_Player1)
			{
				if (AreRectOverlapping(m_ViewRect, m_Player1->GetGameObject().GetTransform().GetRect()))
				{
					m_Projectile->Shoot(pos, Vector{ m_ShootForce * dir, 0 }, m_BolderFriction, 0, 0, 0);
					m_ShootingCooldown.Activate();
				}
			}
			else if (m_Player2)
			{
				if (AreRectOverlapping(m_ViewRect, m_Player2->GetGameObject().GetTransform().GetRect()))
				{
					m_Projectile->Shoot(pos, Vector{ m_ShootForce * dir, 0 }, m_BolderFriction, 0, 0, 0);
					m_ShootingCooldown.Activate();
				}
			}
		}
	}
	else
		m_ShootingCooldown.Tick();
	m_Physics->AcessAcceleration().x = dir * m_WalkSpeed;
}

void tait::Enemy::GapCap()
{
	if (m_GameObject.GetTransform().GetPosition().y > m_LevelBottom)
		m_GameObject.GetTransform().SetPosition(m_GameObject.GetTransform().GetPosition().x, m_LevelTop - m_GameObject.GetTransform().GetSize().y);
}
