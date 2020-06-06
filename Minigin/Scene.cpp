#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <algorithm>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<SceneObject>& object)
{
	m_Objects.push_back(object);
	auto objSort = [](const SceneObject& obj1, const SceneObject& obj2) 
	{
		return obj1.GetLayerId() < obj2.GetLayerId();
	};
	std::sort(m_Objects.begin(), m_Objects.end(), objSort);
}

void dae::Scene::PreUpdate()
{
	for (auto& object : m_Objects)
		object->PreUpdate();
}

void Scene::Update()
{
	for(auto& object : m_Objects)
	{
		object->Update();
	}
}

void dae::Scene::PostUpdate()
{
	for (auto& object : m_Objects)
		object->PostUpdate();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

