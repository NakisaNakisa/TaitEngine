#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void SetActiveScene(const std::string& name);
		void SetActiveScene(int id);
		Scene& GetActiveScene() const { return *m_ActiveScene; }

		void PreUpdate();
		void Update();
		void PostUpdate();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::shared_ptr<Scene> m_ActiveScene{ nullptr };
		std::vector<std::shared_ptr<Scene>> m_Scenes;
		void SetObjects(bool isActive);
	};
}
