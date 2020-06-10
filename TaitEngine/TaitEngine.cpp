#include "TaitPCH.h"
#include "TaitEngine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "SpriteRenderComponent.h"
#include "CameraComponent.h"

using namespace std;
using namespace std::chrono;

void tait::TaitEngine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	int w, h;
	if (m_FullScreen)
	{
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		w = DM.w;
		h = DM.h;
	}
	else
	{
		w = m_W;
		h = m_H;
	}
	
	m_Window = SDL_CreateWindow(
		"TaitEngine",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		w,
		h,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void tait::TaitEngine::LoadGame()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	SceneManager::GetInstance().SetActiveScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->SetLayerId((int)RenderLayers::Background_0);
	RenderComponent* rc = go->AddComponent<RenderComponent>();
	rc->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	rc = go->AddComponent<RenderComponent>();
	rc->SetTexture("logo.png");
	go->SetPosition(216, 180);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	SpriteRenderComponent* src = go->AddComponent<SpriteRenderComponent>();
	src->SetSprite("GreenDragon.png", 8, 2, 0.15f, -1);
	go->SetPosition(216, 250);
	src->SetSize(Vector{ 30,40 });
	src->SetAmount(8);
	src->SetStartFrame(0);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent<CameraComponent>();
	scene.Add(go);
	scene.FindCamera();


	go = std::make_shared<GameObject>();
	m_pFPSRC = go->AddComponent<RenderComponent>();
	
	go->SetPosition(10, 20);
	scene.Add(go);
}

void tait::TaitEngine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void tait::TaitEngine::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time = Time::GetInstance();
		time.Create();

		bool doContinue = true;
		while (doContinue)
		{
			time.Update();
			doContinue = input.ProcessInput();
			sceneManager.PreUpdate();
			sceneManager.Update();
			sceneManager.PostUpdate();
			renderer.Render();	
			MiniUpdate();
		}
	}

	Cleanup();
}

void tait::TaitEngine::MiniUpdate()
{
	int fps = Time::GetInstance().GetFPS();
	m_pFPSRC->SetText(std::to_string(fps).c_str());

	//CameraComponent* cam = SceneManager::GetInstance().GetActiveScene().GetCamera();
	//float dt = Time::GetInstance().GetDeltaTime();
	//
	//Vector moveRight = cam->GetGameObject().GetTransform().GetPosition() + Vector{ dt * 20, 0 };
	//cam->GetGameObject().GetTransform().SetPosition(moveRight);
}
