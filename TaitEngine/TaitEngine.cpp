#include "TaitPCH.h"
#include "TaitEngine.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "SpriteRenderComponent.h"
#include "CameraComponent.h"
#include "ThreadProviderh.h"

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

void tait::TaitEngine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void tait::TaitEngine::Run()
{
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
		}

		ThreadProvider::GetInstance().CleanUp();
	}

	Cleanup();
}

void tait::TaitEngine::SetWindowSize(int w, int h)
{
	m_W = w;
	m_H = h;
}

void tait::TaitEngine::SetFullScreen(bool isFullscreen)
{
	m_FullScreen = isFullscreen;
}
