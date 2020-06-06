#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class CameraComponent;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(const std::shared_ptr<GameObject>& object);
		void FindCamera();
		void SetActiveCamera(CameraComponent* activeCam);
		CameraComponent* GetCamera() const { return m_ActiveCamera; }

		void PreUpdate();
		void Update();
		void PostUpdate();
		void Render() const;

		const std::string& GetName() const { return m_Name; }

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		CameraComponent* m_ActiveCamera{ nullptr };

		std::string m_Name;
		std::vector < std::shared_ptr<GameObject>> m_Objects{};

		static unsigned int m_IdCounter; 
	};

}
