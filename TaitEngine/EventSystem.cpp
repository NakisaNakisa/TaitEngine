#include "TaitPCH.h"
#include "EventSystem.h"
#include "Observer.h"

std::vector<tait::Observer*> tait::EventSystem::m_Observers{};

void tait::EventSystem::AddObserver(Observer* newObserver)
{
	if (!HasObserver(newObserver))
		m_Observers.push_back(newObserver);
}

void tait::EventSystem::RemoveObserver(Observer* observerToRemove)
{
	std::vector<Observer*>::const_iterator it;
	if (HasObserver(observerToRemove, it))
		m_Observers.erase(it);
}

void tait::EventSystem::TriggerEvent(const Component& source, Event event)
{
	for (Observer* observer : m_Observers)
		observer->Notify(source, event);
}

bool tait::EventSystem::HasObserver(Observer* observer)
{
	return std::find(m_Observers.begin(), m_Observers.end(), observer) != m_Observers.end();
}

bool tait::EventSystem::HasObserver(Observer* observer, std::vector<Observer*>::const_iterator& it)
{
	it = std::find(m_Observers.begin(), m_Observers.end(), observer);
	return it != m_Observers.end();
}

