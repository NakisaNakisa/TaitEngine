#include "TaitPCH.h"
#include "GameManager.h"
#include "LevelTransitionState.h"
#include "Player.h"
#include "CameraComponent.h"
#include "IngameState.h"
#include "MenuState.h"
#include "SpriteRenderComponent.h"
#include "GameObject.h"

tait::GameManager::GameManager(GameObject* go, std::shared_ptr<tait::GameObject>& playerGo, std::shared_ptr<tait::GameObject>& player2Go, CameraComponent* camera, RenderComponent* background,
	RenderComponent* cursor, RenderComponent* text1, RenderComponent* text2, RenderComponent* text3)
	: Component(*go)
	, m_PlayerGo{ playerGo }
	, m_Player2Go{ player2Go }
{
	m_LevelTransition = new LevelTransitionState(playerGo->GetComponent<Player>(), player2Go->GetComponent<Player>(), camera, &m_GameState);
	m_GameState.AddState(m_LevelTransition);
	m_Ingame = new IngameState(playerGo, player2Go, &m_GameState, *this);
	m_GameState.AddState(m_Ingame);
	m_Menu = new MenuState(camera, &m_GameState, background, cursor, text1, text2, text3, this);
	m_GameState.AddState(m_Menu);
	m_GameState.Transition(m_Ingame);
	m_GameState.Transition(m_Menu);
	SceneManager::GetInstance().GetScene(m_LevelId)->Add(m_PlayerGo);
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

void tait::GameManager::LevelFinished()
{
	if (m_LevelId >= m_MaxLevels)
	{
		SceneManager::GetInstance().GetScene(m_LevelId)->Remove(m_PlayerGo);
		if(m_TwoPlayers)
			SceneManager::GetInstance().GetScene(m_LevelId)->Remove(m_Player2Go);
		SceneManager::GetInstance().GetScene(m_LevelId)->SetActiveState(false);
		m_LevelId = 1;
		SceneManager::GetInstance().GetScene(0)->SetActiveState(true);
		m_GameState.Transition(m_Menu);
		return;
	}
	SceneManager::GetInstance().GetScene(0)->SetActiveState(false);
	m_LevelTransition->SetOldScene(&SceneManager::GetInstance().GetActiveScene());
	SceneManager::GetInstance().GetScene(m_LevelId)->Remove(m_PlayerGo);
	if(m_TwoPlayers)
		SceneManager::GetInstance().GetScene(m_LevelId)->Remove(m_Player2Go);
	m_LevelId++;
	SceneManager::GetInstance().GetScene(m_LevelId)->Add(m_PlayerGo);
	if(m_TwoPlayers)
		SceneManager::GetInstance().GetScene(m_LevelId)->Add(m_Player2Go);
	m_GameState.Transition(m_LevelTransition);
}

void tait::GameManager::SetTwoPlayers()
{
	m_Ingame->SetTwoPlayers(true);
	m_LevelTransition->SetTwoPlayers(true);
	m_TwoPlayers = true;
	if (m_TwoPlayers)
		SceneManager::GetInstance().GetScene(m_LevelId)->Add(m_Player2Go);
}

