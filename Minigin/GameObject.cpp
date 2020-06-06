#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject()
{
	for (Component* c : m_Components)
		delete c;
	m_Components.clear();
}

inline void dae::GameObject::RemoveComponentHelper(size_t id)
{
	size_t size = m_Components.size();
	if (id < size - 1)
	{
		delete m_Components[id];
		m_Components[id] = m_Components[size - 1];
	}
	m_Components.pop_back();
}

void dae::GameObject::PreUpdate()
{
	for (Component* c : m_Components)
		if (c->IsActive())
			c->PreUpdate();
}

void dae::GameObject::Update()
{
	for (Component* c : m_Components)
		if (c->IsActive())
			c->Update();
}

void dae::GameObject::PostUpdate()
{
	for (Component* c : m_Components)
		if (c->IsActive())
			c->PostUpdate();
}

void dae::GameObject::Render() const
{
	for (Component* c : m_Components)
		if (c->IsActive())
			c->Render();
}


void dae::GameObject::RemoveComponent(Component* toRemove)
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

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y);
}

dae::Transform& dae::GameObject::GetTransform()
{
	return m_Transform;
}
