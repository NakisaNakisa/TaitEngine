#pragma once
#include <string>
#include "InputManager.h"

namespace tait
{
	class Command
	{
	public:
		virtual void Execute() = 0;
		virtual ~Command() {};
		void SetName(std::string& name);
		void SetHotkey(int hotkeyId);
		void SetHotkey(ControllerButton hotkeyId);
		ControllerButton GetHotkey() const;
		const std::string& GetName() const;
	protected:
		ControllerButton m_Hotkey{};
		std::string m_Name{};
		Command() {};
	};
}



