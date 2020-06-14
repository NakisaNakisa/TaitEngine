#include "TaitPCH.h"
#include "IngameObserver.h"

tait::IngameObserver::IngameObserver(IngameState* igs)
	: m_IGS{ igs }
	, m_TwoPlayers{ igs->IsTwoPlayers() }
{
}

void tait::IngameObserver::Notify(const Component&, Event e)
{
	if (e == Event::PLAYER_DIED)
	{
		if (!m_TwoPlayers)
			m_IGS->GameOver();
		else
		{
			if (m_PlayerDied)
				m_IGS->GameOver();
			m_PlayerDied = true;
		}
	}
	if (e == Event::ENEMY_DIED)
	{
		m_IGS->EnemyDied();
	}
}
