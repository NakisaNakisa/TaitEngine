#include "TaitPCH.h"
#include "StateMachine.h"

void tait::Statemachine::AddState(State* newState)
{
	auto it = std::find(m_States.begin(), m_States.end(), newState);
	if (it == m_States.end())
		m_States.push_back(newState);
}

void tait::Statemachine::RemoveState(State* stateToRemove)
{
	auto it = std::find(m_States.begin(), m_States.end(), stateToRemove);
	if (it != m_States.end())
		m_States.erase(it);
}

void tait::Statemachine::Transition(State* stateToTransitionTo)
{
	auto it = std::find(m_States.begin(), m_States.end(), stateToTransitionTo);
	if (it != m_States.end())
	{
		if (m_CurrentState)
			m_CurrentState->Exit();
		m_CurrentState = stateToTransitionTo;
		m_CurrentState->Enter();
	}
}

void tait::Statemachine::Update()
{
	if (m_CurrentState)
		m_CurrentState->Run();
}


