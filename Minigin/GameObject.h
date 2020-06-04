#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Component.h"
#include "RenderComponent.h"

namespace dae
{
	class Texture2D;
	class GameObject final : public SceneObject
	{
	public:

		void PreUpdate() override;
		void Update() override;
		void PostUpdate() override;
		void Render() const override;

		template <typename T>
		inline T* AddComponent();
		template <typename T>
		void RemoveComponent();
		void RemoveComponent(Component* toRemove);

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		Transform& GetTransform();

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		//std::shared_ptr<Texture2D> m_Texture{};
		std::vector<Component*> m_Components;

		void RemoveComponentHelper(size_t id);
	};
}

template <typename T>
inline T* dae::GameObject::AddComponent()
{
	if (std::is_base_of<dae::Component, T>::value)
	{
		T* newT = new T(*this);
		m_Components.push_back(newT);
		return newT;
	}
	return nullptr;
}

template<typename T>
inline void dae::GameObject::RemoveComponent()
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		if (typeid(T*) == typeid(m_Components[i]))
		{
			RemoveComponentHelper(i);
			break;
		}
	}
}

