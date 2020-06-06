#include "MiniginPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <algorithm>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);
	auto objSort = [](const std::shared_ptr<GameObject>& obj1, const std::shared_ptr<GameObject>& obj2)
	{
		return obj1->GetLayerId() < obj2->GetLayerId();
	};
	std::sort(m_Objects.begin(), m_Objects.end(), objSort);
}

void dae::Scene::FindCamera()
{
	for (auto& object : m_Objects)
	{
		CameraComponent* c = object->GetComponent<CameraComponent>();
		if (c != nullptr)
			m_ActiveCamera = c;
	}
}

void dae::Scene::SetActiveCamera(CameraComponent* activeCam)
{
	m_ActiveCamera = activeCam;
}

void dae::Scene::PreUpdate()
{
	for (auto& object : m_Objects)
		if(object->IsActive())
			object->PreUpdate();
}

void Scene::Update()
{
	for(auto& object : m_Objects)
		if (object->IsActive())
			object->Update();
}

void dae::Scene::PostUpdate()
{
	for (auto& object : m_Objects)
		if (object->IsActive())
			object->PostUpdate();
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
		if (object->IsActive())
			object->Render();
}

