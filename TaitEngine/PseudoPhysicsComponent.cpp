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
	, m_Gravity{ 150.f }
	, m_Friction{ 200.f }
	, m_Velocity{}
	, m_Acceleration{}
	, m_MaxVelocity{ 70, 150 }
{
	if (!m_Collider)
		m_Collider = m_GameObject.AddComponent<ColliderComponent>();
	//CollisionObserver::AddPhysicsComponent(this);
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
	//Vector memoryVel{ m_Velocity };
	for (ColliderComponent* col : colliders)
	{
		//Vector vel = m_Velocity;
		if (col != m_Collider && col->GetGameObject().GetTag() != m_Collider->GetGameObject().GetTag())
		{
			if (AreRectOverlapping(m_Collider->GetCoords(), col->GetCoords()))
			{
				if (!col->IsTrigger())
				{
					if (!col->IgnoreCollision(m_Velocity))
					{
						col->MoveBack(m_GameObject.GetTransform(), m_Velocity);
					}
				}
				else
				{
					if (m_Other == col)
					{
						EventSystem::TriggerEvent(*m_Other, Event::TRIGGER_INSIDE);
						m_GameObject.OnTriggerStay(m_Other);
						//std::cout << "Trigger inside" << std::endl;
					}
					else
					{
						m_Other = col;
						m_GameObject.OnTriggerEnter(m_Other);
						EventSystem::TriggerEvent(*m_Other, Event::TRIGGER_ENTERED);
						//std::cout << "Trigger enter" << std::endl;
					}
				}
			}
			else
			{
				if (m_Other == col)
				{
					m_GameObject.OnTriggerExit(m_Other);
					m_Other = nullptr;
					EventSystem::TriggerEvent(*m_Other, Event::TRIGGER_EXIT);
					//std::cout << "Trigger exit" << std::endl;
				}
			}
		}
	}
	//m_Velocity = memoryVel;
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
				Vector foot1{ m_GameObject.GetTransform().GetPosition() + Vector{ 0, m_GameObject.GetTransform().GetSize().y + 2 } };
				Vector foot2{ m_GameObject.GetTransform().GetPosition() + Vector{ 0, 2 } +m_GameObject.GetTransform().GetSize() };
				if (IsPointInRect(col->GetCoords(), foot1) || IsPointInRect(col->GetCoords(), foot2))
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
