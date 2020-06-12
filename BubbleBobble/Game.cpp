#include "TaitPCH.h"
#include "Game.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "GameAudio.h"
#include "Locator.h"
#include <fstream>
#include "ColliderComponent.h"
#include "CharacterControllerComponent.h"
#include "SpriteRenderComponent.h"

using namespace tait;

Game::Game(int windowW, int windowH)
{
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	m_MainMenu = &SceneManager::GetInstance().CreateScene("MainMenu");
	
	auto go = std::make_shared<GameObject>();
	auto renderer = go->AddComponent<RenderComponent>();
	renderer->SetTexture("Title.png");
	//renderer->SetSize(Vector{ (float)windowW , (float)windowH });
	m_MainMenu->Add(go);


	m_Camera = std::make_shared<GameObject>();
	m_Camera->AddComponent<CameraComponent>();
	m_MainMenu->Add(m_Camera);
	m_MainMenu->FindCamera();

	auto gameAudio = std::make_shared<GameAudio>();
	Locator::Initialize();
	Locator::Provide(&*gameAudio);

	SceneManager::GetInstance().SetActiveScene((int)Levels::MainMenu);

	ParseLevels();
}

void Game::CleanUp()
{
	Locator::Cleanup();
}

void Game::ParseLevels()
{
	for (int i = 1; i <= m_NrOfLevels; i++)
	{
		std::ifstream levelFile{ "../Data/Level_" + std::to_string(i) + ".txt" };
		if (!levelFile.is_open())
			continue;
		std::string line{};
		std::getline(levelFile, line);
		std::string name{ "Level" + std::to_string(i) };
		m_Levels.push_back(&SceneManager::GetInstance().CreateScene(name));
		int id = i - 1;
		m_Levels[id]->Add(m_Camera);
		m_Levels[id]->FindCamera();
		auto go = std::make_shared<GameObject>();
		auto img = go->AddComponent<RenderComponent>();
		img->SetTexture(name + ".png");
		while (true)
		{
			std::getline(levelFile, line);
			if (line == "c")
				break;
			auto col = go->AddComponent<ColliderComponent>();
			float v[4]{};
			std::stringstream ss{ line };
			std::string val{};
			for (int i = 0; i < 4; i++)
			{
				std::getline(ss, val, ',');
				v[i] = std::stof(val);
			}
			col->SetRect(Rect{ v[0],v[1],v[2],v[3] });
			m_Levels[id]->AddCollider(col);
		}
		while (true)
		{
			std::getline(levelFile, line);
			if (line == "e")
				break;
			auto col = go->AddComponent<ColliderComponent>();
			float v[4]{};
			std::stringstream ss{ line };
			std::string val{};
			for (int i = 0; i < 4; i++)
			{
				std::getline(ss, val, ',');
				v[i] = std::stof(val);
			}
			col->SetRect(Rect{ v[0],v[1],v[2],v[3] });
			col->SetIgnoreUp(true);
			m_Levels[id]->AddCollider(col);
		}
		m_Levels[id]->Add(go);
		go = std::make_shared<GameObject>();
		auto col = go->AddComponent<ColliderComponent>();
		col->SetSize(Vector{ 32,32 });
		col->SetStatic(false);
		go->AddComponent<PseudoPhysicsComponent>();
		auto sprite = go->AddComponent<SpriteRenderComponent>();
		sprite->SetSprite("Character.png", 8, 12, 0.2f, 8);
		sprite->SetAmount(8);
		sprite->SetStartFrame(0);
		sprite->SetSize(Vector{ 32, 32 });
		auto player = go->AddComponent<CharacterControllerComponent>();
		player->GetGameObject().SetPosition(50, 424 - 64);
		m_Levels[id]->Add(go);
		SceneManager::GetInstance().SetActiveScene((int)Levels::Level1);
	}
}
