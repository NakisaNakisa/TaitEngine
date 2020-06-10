#pragma once
#include "GameObject.h"

struct SDL_Window;
namespace tait
{
	class TaitEngine
	{
	public:
		void Initialize();
		void LoadGame() /*const*/;
		void Cleanup();
		void Run();
		void SetWindowSize(int w, int h);
		void SetFullScreen(bool isFullscreen);
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SDL_Window* m_Window{};

		RenderComponent* m_pFPSRC;
		int m_W{ 640 }, m_H{ 480 };
		bool m_FullScreen{};
		bool m_Demo = false;
	};
}