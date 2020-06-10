#include "TaitPCH.h"
#include "Game.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "GameAudio.h"
#include "Locator.h"

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


	go = std::make_shared<GameObject>();
	go->AddComponent<CameraComponent>();
	m_MainMenu->Add(go);
	m_MainMenu->FindCamera();

	auto gameAudio = std::make_shared<GameAudio>();
	Locator::Initialize();
	Locator::Provide(&*gameAudio);

	SceneManager::GetInstance().SetActiveScene((int)Levels::MainMenu);
}

void Game::CleanUp()
{
	Locator::Cleanup();
}
