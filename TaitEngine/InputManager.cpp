#include "TaitPCH.h"
#include "InputManager.h"
#include <Windows.h>
#include <Xinput.h>
#include "Command.h"


bool tait::InputManager::ProcessInput()
{
	for (DWORD i = 0; i < 4; i++)
	{
		ZeroMemory(&m_CurrentState[i], sizeof(XINPUT_STATE));
		XInputGetState(i, &m_CurrentState[i]);		
	}
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {
			m_CurrentKey = e.key.keysym.sym;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			m_CurrentMouseButton = e.button;
		}
	}
	return true;
}

bool tait::InputManager::IsControllerButtonPressed(tait::ControllerButton button, int playerId) const
{
	switch (button)
	{
	case tait::ControllerButton::DPadUp:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case tait::ControllerButton::DPadDown:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case tait::ControllerButton::DPadLeft:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case tait::ControllerButton::DPadRight:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case tait::ControllerButton::Start:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_START;
	case tait::ControllerButton::Back:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_BACK;
	case tait::ControllerButton::LeftThumb:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB;
	case tait::ControllerButton::RightThumb:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB;
	case tait::ControllerButton::LeftShoulder:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER;
	case tait::ControllerButton::RightShoulder:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER;
	case ControllerButton::ButtonA:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState[playerId].Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	case tait::ControllerButton::None:
	default: return false;
	}
}

bool tait::InputManager::IsKeyDown(SDL_Keycode key) const
{
	return key == m_CurrentKey;
}

//source https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput#multiple-controllers

tait::Vector tait::InputManager::ControllerStickValues(int playerId, bool isLeftStick) const
{
	float x{};
	float y{};
	int DeadZone = isLeftStick ? XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE : XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
	if (isLeftStick)
	{
		x = m_CurrentState[playerId].Gamepad.sThumbLX;
		y = m_CurrentState[playerId].Gamepad.sThumbLY;
	}
	else
	{
		x = m_CurrentState[playerId].Gamepad.sThumbRX;
		y = m_CurrentState[playerId].Gamepad.sThumbRY;
	}

	//determine how far the controller is pushed
	float magnitude = sqrt(x * x + y * y);

	if (magnitude == 0)
		return Vector{};

	//determine the direction the controller is pushed
	float normalizedLX = x / magnitude;
	float normalizedLY = y / magnitude;

	float normalizedMagnitude = 0;

	//check if the controller is outside a circular dead zone
	if (magnitude > DeadZone)
	{
		//clip the magnitude at its expected maximum value
		if (magnitude > 32767) magnitude = 32767;

		//adjust magnitude relative to the end of the dead zone
		magnitude -= DeadZone;

		//optionally normalize the magnitude with respect to its expected range
		//giving a magnitude value of 0.0 to 1.0
		normalizedMagnitude = magnitude / (32767 - DeadZone);
	}
	else //if the controller is in the deadzone zero out the magnitude
	{
		magnitude = 0.0;
		normalizedMagnitude = 0.0;
	}
	return Vector{ normalizedLX, normalizedLY };
}
