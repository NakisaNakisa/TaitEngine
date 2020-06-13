#include "TaitPCH.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "TaitEngine.h"
#include "Game.h"

int main(int, char* []) {
	const int ww{ 512 };
	const int wh{ 424 };
	tait::TaitEngine engine;
	engine.SetFullScreen(false);
	engine.SetWindowSize(ww, wh);
	engine.Initialize();
	Game game{ ww , wh };
	engine.Run();
	game.CleanUp();
	return 0;
}