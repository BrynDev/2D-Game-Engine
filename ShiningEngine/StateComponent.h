#pragma once
#include "Component.h"
#include <unordered_set>

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

		virtual void Render(const glm::vec3& pos) /*const*/ override;
		virtual void Update(const float timeStep) override;
	private:
		std::unordered_set<State*> m_pStates;
		State* m_pCurrentState;
		GameObject* m_pOwner;
	};
}


