#pragma once
#include "Observer.h"
#include "IngameState.h"

namespace tait
{
	class IngameObserver : public Observer
	{
	public:
		IngameObserver(IngameState* igs);
		virtual ~IngameObserver() = default;
		virtual void Notify(const Component& source, Event e);
		void SetTwoPlayers() { m_TwoPlayers = true; }
	private:
		IngameState* m_IGS;
		bool& m_TwoPlayers;
		bool m_PlayerDied{};
	};
}