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
		Vector ControllerStickValues(int playerId, bool isLeftStick) const;
	private:
		XINPUT_STATE m_CurrentState[4]{};
		SDL_Keycode m_CurrentKey{};
		SDL_MouseButtonEvent m_CurrentMouseButton{};
	};
}