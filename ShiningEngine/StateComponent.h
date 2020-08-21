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
		State* const GetCurrentState() const noexcept;

		template<typename T>
		void ChangeState() noexcept;

		template<typename T>
		const bool IsCurrentState() noexcept;
	private:
		std::set<State*> m_pStates;
		State* m_pCurrentState;
		State* m_pNextState;
		GameObject* m_pOwner;
		bool m_NeedsSwap;
	};
}


template<typename T>
void Shining::StateComponent::ChangeState() noexcept
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
			m_pNextState = pState;
			m_NeedsSwap = true;
			return;
		}
	}

}

template<typename T>
const bool Shining::StateComponent::IsCurrentState() noexcept
{
	return(typeid(T) == typeid(*m_pCurrentState));
	
}

