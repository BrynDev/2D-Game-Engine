#pragma once
#include "Component.h"
#include <set>
#include "State.h"
#include <typeinfo>

namespace Shining
{
	class GameObject;
	class State;

	class StateComponent final : public Component
	{
	public:
		StateComponent(State* pStartingState, GameObject* pOwner);
		virtual ~StateComponent();
		StateComponent(const StateComponent& other) = delete;
		StateComponent& operator=(const StateComponent& rhs) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(StateComponent&& rhs) = delete;

		virtual void Render(const glm::vec2& pos) /*const*/ override;
		virtual void Update(const float timeStep) override;
		virtual void SwapBuffer() noexcept override;
		void AddState(State* pStateToAdd) noexcept;

		//data variable used to optionally pass aditional data to the state, left to the user
		template<typename T>
		void ChangeState() noexcept;
	private:
		std::set<State*> m_pStates;
		State* m_pCurrentState;
		State* m_pNextState;
		GameObject* m_pOwner;
		bool m_NeedsSwap;
	};
}


template<typename T>
void Shining::StateComponent::ChangeState(/*const glm::vec4& data*/) noexcept
{
	if (typeid(T) == typeid(m_pCurrentState))
	{
		//state is not being changed
		return;
	}

	for (State* pState : m_pStates)
	{
		if (typeid(T) == typeid(*pState))
		{
			m_pCurrentState->OnExit(m_pOwner);
			//m_pCurrentState = pState;
			//m_pCurrentState->OnEntry(m_pOwner); //OnEntry of new state gets called in this component's SwapBuffer function
			m_pNextState = pState;
			m_NeedsSwap = true;
			return;
		}
	}

}

