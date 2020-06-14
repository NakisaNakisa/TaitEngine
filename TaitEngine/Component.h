#pragma once

namespace tait
{
	class GameObject;
	class ColliderComponent;
	class Component
	{
	public:
		virtual void Update() {};
		virtual void PreUpdate() {};
		virtual void PostUpdate() {};
		virtual void Render() const {};
		virtual ~Component() = default;

		virtual void OnTriggerEnter(ColliderComponent*) {};
		virtual void OnTriggerExit(ColliderComponent*) {};
		virtual void OnTriggerStay(ColliderComponent*) {};

		void SetActiveStatus(bool isActive) { m_IsActive = isActive; }
		bool IsActive() const { return m_IsActive; }

		GameObject& GetGameObject() const { return m_GameObject; }
		
	protected:
		Component(GameObject& go) : m_GameObject{ go } { };
		GameObject& m_GameObject;
		bool m_IsActive{ true };
	};
}
