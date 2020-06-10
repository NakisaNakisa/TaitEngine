#include "TaitPCH.h"
#include "CollisionObserver.h"
#include "PseudoPhysicsComponent.h"

std::vector<tait::PseudoPhysicsComponent*> tait::CollisionObserver::m_PhysicsComponents{};

void tait::CollisionObserver::Notify(const Component&, Event)
{

}

void tait::CollisionObserver::AddPhysicsComponent(PseudoPhysicsComponent* physicsComponent)
{
	m_PhysicsComponents.push_back(physicsComponent);
}
