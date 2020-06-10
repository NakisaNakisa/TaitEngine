#include "TaitPCH.h"
#include "Command.h"
#include "InputManager.h"

void tait::Command::SetName(std::string& name)
{
	m_Name = name;
}

void tait::Command::SetHotkey(int hotkeyId)
{
	m_Hotkey = (ControllerButton)hotkeyId;
}

void tait::Command::SetHotkey(ControllerButton hotkeyId)
{
	m_Hotkey = hotkeyId;
}

tait::ControllerButton tait::Command::GetHotkey() const
{
	return m_Hotkey;
}

const std::string& tait::Command::GetName() const
{
	return m_Name;
}
