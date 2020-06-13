#pragma once
#include "Component.h"

namespace tait
{
	class SpriteRenderComponent;
	class ColliderComponent;
	class PseudoPhysicsComponent;

	class Enemy : public Component
	{
	public:
		Enemy(GameObject& go);
	private:
		SpriteRenderComponent* m_Renderer;
		ColliderComponent* m_Collider;
		PseudoPhysicsComponent* m_Physics;
	};
}