#pragma once
#include "Scene.h"

class Game
{
	enum class Levels
	{
		MainMenu,
		Level1,
		Level2,
		Level3
	};
public:
	Game(int windowW, int windowH);
	void CleanUp();
	void ParseLevels();
private:
	const int m_NrOfLevels{ 1 };
	tait::Scene* m_MainMenu;
	std::vector<tait::Scene*> m_Levels;
};