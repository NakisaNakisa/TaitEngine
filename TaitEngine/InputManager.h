#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <SDL.h>
#include <vector>
#include <string>

namespace tait
{
	class Command;
	enum class ControllerButton
	{
		DPadUp,
		DPadDown,
		DPadLeft,
		DPadRight,
		Start,
		Back,
		LeftThumb,
		RightThumb,
		LeftShoulder,
		RightShoulder,
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		None
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsControllerButtonPressed(ControllerButton button, int playerId) const;
		bool IsKeyDown(SDL_Keycode key) const;
		bool IsKeyPressed(SDL_Keycode key) const;
		bool IsKeyUp(SDL_Keycode key) const;
		Vector ControllerStickValues(int playerId, bool isLeftStick) const;
	private:
		static const int m_MaxKeys{ 10 };
		static const int m_MaxControllers{ 4 };
		XINPUT_STATE m_CurrentState[m_MaxControllers]{};
		SDL_Keycode m_PressedKey[m_MaxKeys]{};
		SDL_Keycode m_CurrentKey[m_MaxKeys]{};
		SDL_Keycode m_ReleasedKey[m_MaxKeys]{};
		SDL_MouseButtonEvent m_CurrentMouseButton{};
	};
}