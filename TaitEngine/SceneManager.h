#pragma once
#include "Singleton.h"

namespace tait
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		void SetActiveScene(const std::string& name);
		void SetActiveScene(int id, bool deactivateLastScene = true);
		Scene& GetActiveScene() const { return *m_ActiveScene; }
		Scene* GetScene(int id) const;
		size_t GetNrOfScenes() const { return m_Scenes.size(); }

		void PreUpdate();
		void Update();
		void PostUpdate();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::shared_ptr<Scene> m_ActiveScene{ nullptr };
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
