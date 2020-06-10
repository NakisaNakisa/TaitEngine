#include "TaitPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void tait::SceneManager::PreUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->PreUpdate();
	}
}

void tait::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		scene->Update();
	}
}

void tait::SceneManager::PostUpdate()
{
	for (auto& scene : m_Scenes)
	{
		scene->PostUpdate();
	}
}

void tait::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

tait::Scene& tait::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

void tait::SceneManager::SetActiveScene(const std::string& name)
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

void tait::SceneManager::SetActiveScene(int id)
{
	m_ActiveScene = m_Scenes[id];
}
