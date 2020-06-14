#pragma once
#include "Component.h"

namespace tait
{
	class Observer;

	enum class Event
	{
		TRIGGER_ENTERED,
		TRIGGER_EXIT,
		TRIGGER_INSIDE,
		PLAYER_DIED,
		ENEMY_DIED
	};

	class EventSystem
	{
	public:
		static void AddObserver(Observer* newObserver);
		static void RemoveObserver(Observer* observerToRemove);
		static void TriggerEvent(const Component& source, Event event);
	private:
		static std::vector<Observer*> m_Observers;

		static bool HasObserver(Observer* observer);
		static bool HasObserver(Observer* observer, std::vector<Observer*>::const_iterator& it);
	};
}