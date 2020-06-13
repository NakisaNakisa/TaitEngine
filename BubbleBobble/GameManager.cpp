#include "TaitPCH.h"
#include "GameManager.h"
#include "LevelTransitionState.h"
#include "Player.h"
#include "CameraComponent.h"
#include "IngameState.h"
#include "MenuState.h"
#include "SpriteRenderComponent.h"

tait::GameManager::GameManager(GameObject* go, Player* player, CameraComponent* camera, RenderComponent* background,
	RenderComponent* cursor, RenderComponent* text1, RenderComponent* text2, RenderComponent* text3)
	: Component(*go)
{
	m_LevelTransition = new LevelTransitionState(player, camera, &m_GameState);
	m_GameState.AddState(m_LevelTransition);
	m_Ingame = new IngameState(player, &m_GameState);
	m_GameState.AddState(m_Ingame);
	m_Menu = new MenuState(player, &m_GameState, background, cursor, text1, text2, text3);
	m_GameState.AddState(m_Menu);
	m_GameState.Transition(m_Ingame);
	m_GameState.Transition(m_Menu);
}

tait::GameManager::~GameManager()
{
	delete m_LevelTransition;
	m_LevelTransition = nullptr;
	delete m_Menu;
	m_Menu = nullptr;
	delete m_Ingame;
	m_Ingame = nullptr;
}

void tait::GameManager::Update()
{
	m_GameState.Update();
}
