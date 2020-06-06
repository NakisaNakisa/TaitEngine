#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::PreUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->PreUpdate();
	}
}

void dae::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::PostUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->PostUpdate();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	for (std::shared_ptr<Scene>& scene : m_Scenes)
	{
		if (scene->GetName() == name)
		{
			m_ActiveScene = scene;
			return;
		}
	}
}

void dae::SceneManager::SetActiveScene(int id)
{
	m_ActiveScene = m_Scenes[id];
}
