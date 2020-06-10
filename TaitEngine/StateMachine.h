#pragma once


namespace tait
{
	class State
	{
	public:
		virtual void Run() = 0;
		virtual void Enter() = 0;
		virtual void Exit() = 0;
	};

	class Statemachine
	{
	public:
		void AddState(State* newState);
		void RemoveState(State* stateToRemove);

		void Transition(State* stateToTransitionTo);
		void Update();
	private:
		std::vector<State*> m_States{};
		State* m_CurrentState{};
	};
}