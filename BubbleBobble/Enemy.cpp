#include "TaitPCH.h"
#include "Enemy.h"
#include "GameObject.h"
#include "Projectile.h"

tait::Enemy::Enemy(GameObject& go, int type)
	: Component(go)
	, m_Collider{ go.GetComponent<ColliderComponent>() }
	, m_Physics{ go.GetComponent<PseudoPhysicsComponent>() }
	, m_Renderer{ go.GetComponent<SpriteRenderComponent>() }
	, m_Type{ type }
{
	m_FloatingDuration.SetTimes(m_FloatTime);
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
	if (!m_IsInBubble)
	{
		bool isLookingLeft = m_Physics->GetVelocity().x > 0;
		if (isLookingLeft != m_IsLookingleft)
		{
			int moveStart{ m_IsLookingleft ? m_MoveLeft : m_MoveRight };
			m_Renderer->SetStartFrame(moveStart + m_TypeOffset * m_Type);
		}
		if (m_Type == 0)
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
}

void tait::Enemy::Enemy1Update()
{
}

void tait::Enemy::Enemy2Update()
{
}
