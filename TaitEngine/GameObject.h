#pragma once
#include "Transform.h"
#include "Component.h"
#include "RenderComponent.h"
#include "CameraComponent.h"
#include "PseudoPhysicsComponent.h"
#include "SpriteRenderComponent.h"

namespace tait
{
	class Texture2D;
	class GameObject final// : public SceneObject
	{
	public:

		void PreUpdate();
		void Update();
		void PostUpdate();
		void Render() const;

		template <typename T>
		inline T* AddComponent();
		template <typename T>
		inline void AddComponent(T* component);
		template <typename T>
		inline T* GetComponent();
		template <typename T>
		void RemoveComponent();
		void RemoveComponent(Component* toRemove);

		//void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		Transform& GetTransform();

		void SetLayerId(int id) { m_LayerId = id; }
		int GetLayerId() const { return m_LayerId; }

		void SetActiveStatus(bool isActive) { m_IsActive = isActive; }
		bool IsActive() const { return m_IsActive; }

		virtual void OnTriggerEnter(ColliderComponent* other);
		virtual void OnTriggerExit(ColliderComponent* other);
		virtual void OnTriggerStay(ColliderComponent* other);

		int GetTag() const { return m_Tag; }
		void SetTag(int tag) { m_Tag = tag; }
		bool IsTag(int compare) { return m_Tag == compare; }

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		std::vector<Component*> m_Components;

		void RemoveComponentHelper(size_t id);
		bool m_IsActive{ true };
		int m_LayerId{};
		int m_Tag{};
	};
}

template <typename T>
inline T* tait::GameObject::AddComponent()
{
	if (std::is_base_of<tait::Component, T>::value)
	{
		T* newT = new T(*this);
		m_Components.push_back(newT);
		return newT;
	}
	return nullptr;
}

template<typename T>
inline void tait::GameObject::AddComponent(T* component)
{
	if (dynamic_cast<Component*>(component))
		m_Components.push_back(component);
}

template<typename T>
inline T* tait::GameObject::GetComponent()
{
	for (Component* c : m_Components)
	{
		if(T* t = dynamic_cast<T*>(c))
			return t;
	}
	return nullptr;
}

template<typename T>
inline void tait::GameObject::RemoveComponent()
{
	for (size_t i = 0; i < m_Components.size(); i++)
	{
		if (T* t = dynamic_cast<T*>(m_Components[i]))
		{
			RemoveComponentHelper(i);
			break;
		}
	}
}

