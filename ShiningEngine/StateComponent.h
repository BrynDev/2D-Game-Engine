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
		void AddState(State* pStateToAdd) noexcept;

		template<typename T>
		void ChangeState() noexcept;
	private:
		std::set<State*> m_pStates;
		State* m_pCurrentState;
		GameObject* m_pOwner;
	};
}


template<typename T>
void Shining::StateComponent::ChangeState() noexcept
{
	for (State* pState : m_pStates)
	{
		if (typeid(T) == typeid(*pState))
		{
			m_pCurrentState->OnExit(m_pOwner);
			m_pCurrentState = pState;
			m_pCurrentState->OnEntry(m_pOwner);
			return;
		}
	}

}

