#include "TaitPCH.h"
#include "PseudoPhysicsComponent.h"
#include "CollisionObserver.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "Time.h"

tait::PseudoPhysicsComponent::PseudoPhysicsComponent(GameObject& go)
	: Component(go)
	, m_Collider{ go.GetComponent<ColliderComponent>() }
	, m_Gravity{ 100.f }
	, m_Friction{ 200.f }
	, m_Velocity{}
	, m_Acceleration{}
	, m_MaxVelocity{ 70, 130 }
{
	if (!m_Collider)
		m_Collider = m_GameObject.AddComponent<ColliderComponent>();
	CollisionObserver::AddPhysicsComponent(this);
}

void tait::PseudoPhysicsComponent::Update()
{
	float dt = Time::GetInstance().GetDeltaTime();
	m_Velocity.y += m_Gravity * dt;
	if (!IsFloatNOTZero(m_Acceleration.x))
	{
		if (m_Velocity.x > 0)
		{
			m_Velocity.x -= m_Friction * dt;
			if (m_Velocity.x < 0)
				m_Velocity.x = 0;
		}
		else if (m_Velocity.x < 0)
		{
			m_Velocity.x += m_Friction * dt;
			if (m_Velocity.x > 0)
				m_Velocity.x = 0;
		}
	}
	m_Acceleration = Vector{};
}

void tait::PseudoPhysicsComponent::PreUpdate()
{
	m_Velocity = m_Velocity + m_Acceleration;
	CapVelocity();
	Vector delta{ m_Velocity * Time::GetInstance().GetDeltaTime() };
	m_GameObject.GetTransform().Translate(delta);
}

void tait::PseudoPhysicsComponent::PostUpdate()
{
	const std::vector<ColliderComponent*>& colliders = SceneManager::GetInstance().GetActiveScene().GetSceneColliders();
	Vector start = m_GameObject.GetTransform().GetPosition();
	for (ColliderComponent* col : colliders)
	{
		if (col != m_Collider)
		{
			if (AreRectOverlapping(m_Collider->GetCoords(), col->GetCoords()))
			{
				if (!col->IgnoreCollision(m_Velocity))
				{
					if (!col->IsTrigger())
					{
						Vector dir = OneVector(m_Velocity);
						col->MoveBack(m_GameObject.GetTransform(), m_Velocity);
					}
					else
					{
						if (m_Other == col)
						{
							EventSystem::TriggerEvent(*m_Other, Event::TRIGGER_INSIDE);
						}
						else
						{
							m_Other = col;
							EventSystem::TriggerEvent(*m_Other, Event::TRIGGER_ENTERED);
						}
					}
				}
			}
			else
			{
				if (m_Other == col)
				{
					m_Other = nullptr;
					EventSystem::TriggerEvent(*m_Other, Event::TRIGGER_EXIT);
				}
			}
		}
	}
}

bool tait::PseudoPhysicsComponent::IsGrounded() const
{
	if (m_Velocity.y > -FLT_EPSILON)
	{
		const std::vector<ColliderComponent*>& colliders = SceneManager::GetInstance().GetActiveScene().GetSceneColliders();
		Vector start = m_GameObject.GetTransform().GetPosition();
		for (ColliderComponent* col : colliders)
		{
			if (col != m_Collider)
			{
				Vector foot = m_GameObject.GetTransform().GetCenter() + Vector{ 0, m_GameObject.GetTransform().GetHalfSize().y + 2 };
				if (IsPointInRect(col->GetCoords(), foot))
					return true;
			}
		}
	}
	return false;
}

tait::Vector& tait::PseudoPhysicsComponent::AcessAcceleration()
{
	return m_Acceleration;
}

void tait::PseudoPhysicsComponent::CapVelocity()
{
	if (m_Velocity.x > m_MaxVelocity.x)
		m_Velocity.x = m_MaxVelocity.x;
	if (m_Velocity.y > m_MaxVelocity.y)
		m_Velocity.y = m_MaxVelocity.y;
	if (m_Velocity.x < -m_MaxVelocity.x)
		m_Velocity.x = -m_MaxVelocity.x;
	if (m_Velocity.y < -m_MaxVelocity.y)
		m_Velocity.y = -m_MaxVelocity.y;
}
