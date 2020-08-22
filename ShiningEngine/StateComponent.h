#pragma once
#include "Component.h"
#include <set>
#include "State.h"
#include <typeinfo>
#include <vector> //TEST

namespace Shining
{
	class GameObject;
	class State;

	class StateComponent final : public Component
	{
	public:
		explicit StateComponent(State* pStartingState, GameObject* pOwner);
		virtual ~StateComponent();
		StateComponent(const StateComponent& other) = delete;
		StateComponent& operator=(const StateComponent& rhs) = delete;
		StateComponent(StateComponent&& other) = delete;
		StateComponent& operator=(StateComponent&& rhs) = delete;

		virtual void Render(const glm::vec2& pos) /*const*/ override;
		virtual void Update(const float timeStep) override;
		virtual void SwapBuffer() noexcept override;
		void AddState(State* pStateToAdd, const unsigned int layerIdx = 0);
		//State* const GetCurrentState() const noexcept;
		State* const GetCurrentState(const unsigned int layerIdx = 0) const;
		void AddNewStateLayer(State* pDefaultState) noexcept;

		/*template<typename T>
		void ChangeState() noexcept;*/

		template<typename T>
		void ChangeState(const unsigned int layerToChangeIdx = 0);

		/*template<typename T>
		const bool IsCurrentState() noexcept;*/

		template<typename T>
		const bool IsCurrentState(const unsigned int layerToCheckIdx = 0);
	private:
		std::vector<std::set<State*>> m_pStateLayers;
		std::vector<State*> m_pCurrentStates;
		std::vector<State*> m_pNextStates;
		GameObject* m_pOwner;
		bool m_NeedsSwap;
		std::vector<bool> m_NeedsSwapVect;
	};
}


/*template<typename T>
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

}*/

template<typename T>
void Shining::StateComponent::ChangeState(const unsigned int layerToChangeIdx)
{
	/*if (typeid(T) == typeid(*m_pCurrentStates[layerToChangeIdx]) )
	{
		//state is not being changed
		return;
	}*/


	for (State* pState : m_pStateLayers[layerToChangeIdx]) //for every state on this layer
	{
		if (typeid(T) == typeid(*pState)) //is this the state to change to
		{
			//m_pCurrentStates[layerToChangeIdx] = pState; //change state
			m_pNextStates[layerToChangeIdx] = pState; //change state
			m_NeedsSwapVect[layerToChangeIdx] = true;
			//m_NeedsSwap = true;
			return;
		}
	}
}

/*template<typename T>
const bool Shining::StateComponent::IsCurrentState() noexcept
{
	return(typeid(T) == typeid(*m_pCurrentState));
	
}*/

template<typename T>
const bool Shining::StateComponent::IsCurrentState(const unsigned int layerToCheckIdx)
{
	return (typeid(T) == typeid(*m_pCurrentStates[layerToCheckIdx]));
}

