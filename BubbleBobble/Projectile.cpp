#include "TaitPCH.h"
#include "Projectile.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"

tait::Projectile::Projectile(std::shared_ptr<GameObject>& go)
	: Component(*go)
	, m_Physics{ go->GetComponent<PseudoPhysicsComponent>() }
	, m_Collider{ go->GetComponent<ColliderComponent>() }
	, m_Renderer{ go->GetComponent<SpriteRenderComponent>() }
{
	m_Collider->SetStatic(false);
	size_t max = SceneManager::GetInstance().GetNrOfScenes();
	for (size_t i = 1; i < max; i++)
		SceneManager::GetInstance().GetScene((int)i)->Add(go);
}

void tait::Projectile::Update()
{
	if (m_FloatDuration.IsActive())
	{
		m_FloatDuration.Tick();
		if (!m_FloatDuration.IsActive())
			Pop();
	}
	if (m_PopDuration.IsActive())
	{
		m_PopDuration.Tick();
		if (!m_PopDuration.IsActive())
		{
			Disappear();
			return;
		}
	}
	if (IsFloatZero(m_Physics->GetVelocity().x))
	{
		if(!m_HasSwitched)
			SwitchMode();
	}
}

void tait::Projectile::SwitchMode()
{
	m_HasSwitched = true;
	m_Physics->SetVelocity(Vector{ 0.1f,0.1f });
	m_Physics->AcessAcceleration().y = m_Gravity;
	m_Physics->SetGravity(m_Gravity);
	m_FloatDuration.Activate();
	if (!m_FloatDuration.IsActive())
		Pop();
	if(m_IsBubble)
		m_Renderer->SetStartFrame(8 * m_PlayerId);
}

void tait::Projectile::Shoot(const Vector& startPosition, const Vector& startAcceleration, float friction, float gravity, float floatDuration, float popDuration)
{
	m_PopDuration.SetTimes(popDuration);
	if (m_IsBubble)
		m_Renderer->SetStartFrame(5 + 8 * m_PlayerId);
	else
		m_Renderer->SetStartFrame(80);
	m_Renderer->SetAmount(1);
	m_IsActive = true;
	m_HasSwitched = false;
	SceneManager::GetInstance().GetActiveScene().AddCollider(m_Collider);
	m_GameObject.SetActiveStatus(true);
	m_GameObject.GetTransform().SetPosition(startPosition);
	m_Physics->SetFriction(friction);
	m_Physics->SetGravity(0);
	m_Physics->SetVelocity(Vector{ 0.1f,0.1f });
	float x = startAcceleration.x;
	m_Physics->AcessAcceleration() = startAcceleration;
	if (x < 0)
		x *= -1;
	m_Physics->SetMaxVelocity(Vector{ x, x });
	m_FloatDuration.SetTimes(floatDuration);
	m_Gravity = gravity;
}

void tait::Projectile::Pop()
{
	m_Renderer->SetStartFrame(32);
	m_Physics->SetVelocity(Vector{ 0,0 });
	m_PopDuration.Activate();
	if (!m_PopDuration.IsActive())
		Disappear();
}

void tait::Projectile::Disappear()
{
	m_GameObject.GetTransform().SetPosition(-50, -50);
	SceneManager::GetInstance().GetActiveScene().RemoveCollider(m_Collider);
	m_GameObject.SetActiveStatus(false);
	SetActiveStatus(false);
}
