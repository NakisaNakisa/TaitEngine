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
	: m_WindowH{ windowH }
	, m_WindowW{ windowW }
{
	Initialize();
	CreateMainMenu();
	ParseLevels();
	CreatePlayer();
	SceneManager::GetInstance().SetActiveScene((int)Levels::MainMenu);
	CreateGameManager();
	//m_Levels[0]->Remove(m_PlayerGo);
	//m_Levels[2]->Add(m_PlayerGo);
	//SceneManager::GetInstance().SetActiveScene((int)Levels::Level3);
	//m_Player->SetLevelStartEnd(windowH * 2, windowH * 3);
	//m_Player->GetGameObject().GetTransform().Translate(Vector{ 0, (float)windowH * 2 });
	//m_Camera->GetTransform().Translate(Vector{ 0,(float)windowH * 2 });
}

void Game::CleanUp()
{
	Locator::Cleanup();
}

void Game::Initialize()
{
	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	auto gameAudio = std::make_shared<GameAudio>();
	Locator::Initialize();
	Locator::Provide(&*gameAudio);
}

void Game::CreateGameManager()
{
	auto go = std::make_shared<GameObject>();
	GameObject* g = &*go;
	m_GameManager = new GameManager(g, m_PlayerGo, &*m_Camera->GetComponent<CameraComponent>(), m_Background, m_Cursor, m_Text1, m_Text2, m_Text3);
	go->AddComponent(m_GameManager);
	m_MainMenu->Add(go);
	for (size_t i = 0; i < m_Levels.size(); i++)
		m_Levels[i]->Add(go);
	SceneManager::GetInstance().GetActiveScene().Remove(m_PlayerGo);
	m_PlayerGo->SetActiveStatus(false);
}

void Game::CreateMainMenu()
{
	m_MainMenu = &SceneManager::GetInstance().CreateScene("MainMenu");

	auto go = std::make_shared<GameObject>();
	go->SetLayerId(1);
	m_Background = go->AddComponent<RenderComponent>();
	m_Background->SetTexture("Title.png");
	m_MainMenu->Add(go);

	go = std::make_shared<GameObject>();
	Vector textSize = Vector{ m_WindowW / 3.f, m_WindowH / 5.f };
	m_Text1 = go->AddComponent<RenderComponent>();
	m_Text1->SetText("SinglePlayer", SDL_Color{255, 255, 255, 255});
	m_Text1->SetSize(textSize);
	m_Text1->GetGameObject().GetTransform().SetPosition(textSize);
	m_MainMenu->Add(go);

	go = std::make_shared<GameObject>();
	m_Text2 = go->AddComponent<RenderComponent>();
	m_Text2->SetText("Co-op (2 Players)", SDL_Color{ 255, 255, 255, 255 });
	m_Text2->SetSize(textSize);
	m_Text2->GetGameObject().GetTransform().SetPosition(textSize + Vector{ 0, textSize.y });
	m_MainMenu->Add(go);

	go = std::make_shared<GameObject>();
	m_Text3 = go->AddComponent<RenderComponent>();
	m_Text3->SetText("Versus", SDL_Color{ 255, 255, 255, 255 });
	m_Text3->SetSize(textSize);
	m_Text3->GetGameObject().GetTransform().SetPosition(textSize + Vector{ 0, textSize.y * 2 });
	m_MainMenu->Add(go);


	go = std::make_shared<GameObject>();
	m_Cursor = go->AddComponent<RenderComponent>();
	m_Cursor->SetTexture("Cursor.png");
	m_MainMenu->Add(go);

	m_Camera = std::make_shared<GameObject>();
	m_Camera->AddComponent<CameraComponent>();
	m_MainMenu->Add(m_Camera);
	m_MainMenu->FindCamera();
}

void Game::ParseLevels()
{
	for (int levelNr = 1; levelNr <= m_NrOfLevels; levelNr++)
	{
		std::ifstream levelFile{ "../Data/Level_" + std::to_string(levelNr) + ".txt" };
		if (!levelFile.is_open())
			return;
		std::string line{};
		std::getline(levelFile, line);
		std::string name{ "Level" + std::to_string(levelNr) };
		m_Levels.push_back(&SceneManager::GetInstance().CreateScene(name));
		int levelid = levelNr - 1;
		m_Levels[levelid]->Add(m_Camera);
		m_Levels[levelid]->FindCamera();
		auto go = std::make_shared<GameObject>();
		go->GetTransform().SetPosition(0, (float)levelid * m_WindowH);
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
			col->SetRect(Rect{ v[0],v[1] + levelid * m_WindowH,v[2],v[3] });
			m_Levels[levelid]->AddCollider(col);
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
			col->SetRect(Rect{ v[0],v[1] + levelid * m_WindowH,v[2],v[3] });
			col->SetIgnoreUp(true);
			m_Levels[levelid]->AddCollider(col);
		}
		m_Levels[levelid]->Add(go);
		m_Levels[levelid]->SetActiveState(false);
	}
}

void Game::CreatePlayer()
{
	const int playerSize = 24;
	m_PlayerGo = std::make_shared<GameObject>();
	m_PlayerGo->SetLayerId(100);
	auto col = m_PlayerGo->AddComponent<ColliderComponent>();
	col->SetSize(Vector{ playerSize,playerSize });
	col->SetStatic(false);
	m_PlayerGo->AddComponent<PseudoPhysicsComponent>();
	auto sprite = m_PlayerGo->AddComponent<SpriteRenderComponent>();
	sprite->SetSprite("Character.png", 8, 12, 0.2f, 8);
	sprite->SetAmount(8);
	sprite->SetStartFrame(0);
	sprite->SetSize(Vector{ playerSize, playerSize });
	auto chContr = m_PlayerGo->AddComponent<CharacterControllerComponent>();
	chContr->GetGameObject().SetPosition(50, 360);
	m_Player = new Player(*m_PlayerGo);
	m_Player->SetLevelStartEnd(0, m_WindowH);
	m_PlayerGo->AddComponent(m_Player);
	m_PlayerGo->SetActiveStatus(false);
}
