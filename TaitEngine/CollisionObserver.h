#pragma once
#include "Observer.h"

namespace tait
{
	class PseudoPhysicsComponent;

	class CollisionObserver : public Observer
	{
	public:
		virtual ~CollisionObserver() = default;
		virtual void Notify(const Component& source, Event e) override;
		static void AddPhysicsComponent(PseudoPhysicsComponent* physicsComponent);
	private:
		static std::vector<PseudoPhysicsComponent*> m_PhysicsComponents;
	};
}