#include "TaitPCH.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "TaitEngine.h"

int main(int, char* []) {
	tait::TaitEngine engine;
	engine.Run();
	return 0;
}