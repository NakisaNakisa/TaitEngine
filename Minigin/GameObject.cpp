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
		c->PreUpdate();
}

void dae::GameObject::Update()
{
	for (Component* c : m_Components)
		c->Update();
}

void dae::GameObject::PostUpdate()
{
	for (Component* c : m_Components)
		c->PostUpdate();
}

void dae::GameObject::Render() const
{
	for (Component* c : m_Components)
		c->Render();
	//const auto pos = m_Transform.GetPosition();
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
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
//
//void dae::GameObject::SetTexture(const std::string& filename)
//{
//	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
//}

void dae::GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

dae::Transform& dae::GameObject::GetTransform()
{
	return m_Transform;
}