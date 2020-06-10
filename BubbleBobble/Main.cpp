#include "TaitPCH.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "TaitEngine.h"
#include "Game.h"

int main(int, char* []) {
	tait::TaitEngine engine;
	engine.SetFullScreen(false);
	engine.SetWindowSize(512, 424);
	engine.Initialize();
	Game game{ 512 , 424 };
	engine.Run();
	game.CleanUp();
	return 0;
}