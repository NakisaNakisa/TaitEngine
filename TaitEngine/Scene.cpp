#include "TaitPCH.h"
#include "Scene.h"
#include "GameObject.h"
#include <algorithm>

using namespace tait;

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

void tait::Scene::FindCamera()
{
	for (auto& object : m_Objects)
	{
		CameraComponent* c = object->GetComponent<CameraComponent>();
		if (c != nullptr)
			m_ActiveCamera = c;
	}
}

void tait::Scene::SetActiveCamera(CameraComponent* activeCam)
{
	m_ActiveCamera = activeCam;
}

void tait::Scene::Activate(bool isActive)
{
	for (auto go : m_Objects)
		go->SetActiveStatus(isActive);
}

void tait::Scene::AddCollider(ColliderComponent* collider)
{
	auto it = std::find(m_Colliders.begin(), m_Colliders.end(), collider);
	if(it == m_Colliders.end())
		m_Colliders.push_back(collider);
}

void tait::Scene::RemoveCollider(ColliderComponent* collider)
{
	auto it = std::find(m_Colliders.begin(), m_Colliders.end(), collider);
	if (it != m_Colliders.end())
		m_Colliders.erase(it);
}

void tait::Scene::PreUpdate()
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

void tait::Scene::PostUpdate()
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

