#pragma once

namespace dae
{
	class GameObject;
	class Component
	{
	public:
		virtual void Update() {};
		virtual void PreUpdate() {};
		virtual void PostUpdate() {};
		virtual void Render() const {};
		virtual ~Component() = default;
		
	protected:
		Component(GameObject& go) : m_GameObject{ go } { };
		GameObject& m_GameObject;
	};
}
