#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "GameManager.h"
#include "Player.h"
#include "RenderComponent.h"
#include "Enemy.h"
#include "Structs.h"
#include "IngameObserver.h"

/// Contains game manager (FSM)
/// Creates all levels, players and enemies

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
private:
	const int m_NrOfLevels{ 3 };
	const int m_WindowH, m_WindowW;
	std::shared_ptr<tait::GameObject> m_Camera{};
	std::shared_ptr<tait::GameObject> m_PlayerGo{};
	std::shared_ptr<tait::GameObject> m_Player2Go{};
	tait::Scene* m_MainMenu;
	std::vector<tait::Scene*> m_Levels;
	tait::GameManager* m_GameManager{};
	tait::Player* m_Player{};
	tait::Player* m_Player2{};
	tait::RenderComponent* m_Background{};
	tait::RenderComponent* m_Text1{};
	tait::RenderComponent* m_Text2{};
	tait::RenderComponent* m_Text3{};
	tait::RenderComponent* m_Cursor{};
	std::vector<tait::Enemy*> m_Enemies{};
	std::vector<tait::Vector> m_EnemyPos{};
	std::vector<int> m_LevelEnemyAmount{};
	tait::IngameObserver* m_IGO;

	void Initialize();
	void CreateGameManager();
	void CreateMainMenu();
	void ParseLevels();
	void CreatePlayer1();
	void CreatePlayer2();
};