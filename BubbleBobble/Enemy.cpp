#include "TaitPCH.h"
#include "Enemy.h"
#include "GameObject.h"

tait::Enemy::Enemy(GameObject& go)
	: Component(go)
	, m_Collider{ go.GetComponent<ColliderComponent>() }
	, m_Physics{ go.GetComponent<PseudoPhysicsComponent>() }
	, m_Renderer{ go.GetComponent<SpriteRenderComponent>() }
{
}
