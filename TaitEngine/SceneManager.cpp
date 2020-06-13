#include "TaitPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void tait::SceneManager::PreUpdate()
{
	for (auto& scene : m_Scenes)
	{
		if (scene->IsActive())
			scene->PreUpdate();
	}
}

void tait::SceneManager::Update()
{
	for(auto& scene : m_Scenes)
	{
		if(scene->IsActive())
			scene->Update();
	}
}

void tait::SceneManager::PostUpdate()
{
	for (auto& scene : m_Scenes)
	{
		if (scene->IsActive())
			scene->PostUpdate();
	}
}

void tait::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->IsActive())
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

tait::Scene* tait::SceneManager::GetScene(int id) const
{
	if (id < (int)m_Scenes.size())
		return &*m_Scenes[id];
	return nullptr;
}

void tait::SceneManager::SetActiveScene(int id, bool deactivateLastScene)
{
	if (deactivateLastScene)
	{
		if (m_ActiveScene)
			m_ActiveScene->SetActiveState(false);
	}
	m_ActiveScene = m_Scenes[id];
	m_ActiveScene->SetActiveState(true);
}
