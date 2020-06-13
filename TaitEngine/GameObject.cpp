#include "TaitPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

void tait::GameObject::OnTriggerEnter(ColliderComponent* other)
{
	for (auto& component : m_Components)
	{
		if (component->IsActive())
			component->OnTriggerEnter(other);
	}
}

void tait::GameObject::OnTriggerExit(ColliderComponent* other)
{
	for (auto& component : m_Components)
	{
		if (component->IsActive())
			component->OnTriggerExit(other);
	}
}

void tait::GameObject::OnTriggerStay(ColliderComponent* other)
{
	for (auto& component : m_Components)
	{
		if (component->IsActive())
			component->OnTriggerStay(other);
	}
}

tait::GameObject::GameObject()
{
	m_Transform.SetPosition(m_Transform.GetPosition());
}

tait::GameObject::~GameObject()
{
	for (Component* c : m_Components)
		delete c;
	m_Components.clear();
}

inline void tait::GameObject::RemoveComponentHelper(size_t id)
{
	size_t size = m_Components.size();
	if (id < size - 1)
	{
		delete m_Components[id];
		m_Components[id] = m_Components[size - 1];
	}
	m_Components.pop_back();
}

void tait::GameObject::PreUpdate()
{
	for (Component* c : m_Components)
		if (c->IsActive())
			c->PreUpdate();
}

void tait::GameObject::Update()
{
	for (Component* c : m_Components)
		if (c->IsActive())
			c->Update();
}

void tait::GameObject::PostUpdate()
{
	for (Component* c : m_Components)
		if (c->IsActive())
			c->PostUpdate();
}

void tait::GameObject::Render() const
{
	for (Component* c : m_Components)
		if (c->IsActive())
			c->Render();
}


void tait::GameObject::RemoveComponent(Component* toRemove)
{
	size_t size = m_Components.size();
	for (size_t i = 0; i < size; i++)
	{
		if (m_Components[i] == toRemove)
		{
			RemoveComponentHelper(i);
			break;
		}
	}
}

void tait::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y);
}

tait::Transform& tait::GameObject::GetTransform()
{
	return m_Transform;
}
