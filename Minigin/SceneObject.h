#pragma once
namespace dae
{
	class SceneObject
	{
	public:
		virtual void PreUpdate() = 0;
		virtual void Update() = 0;
		virtual void PostUpdate() = 0;
		virtual void Render() const = 0;

		int GetLayerId() const { return m_LayerId; }

		SceneObject() = default;
		virtual ~SceneObject() = default;
		SceneObject(const SceneObject& other) = delete;
		SceneObject(SceneObject&& other) = delete;
		SceneObject& operator=(const SceneObject& other) = delete;
		SceneObject& operator=(SceneObject&& other) = delete;
	protected:
		int m_LayerId{};
	};
}
