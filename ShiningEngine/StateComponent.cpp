#include "ShiningEnginePCH.h"
#include "StateComponent.h"
#include "State.h"

Shining::StateComponent::StateComponent(State* pStartingState, GameObject* pOwner)
	:Component()
	, m_pCurrentState{pStartingState}
	, m_pOwner{pOwner}
{
	m_pStates.insert(pStartingState);
}

void Shining::StateComponent::Render(const glm::vec3& /*pos*/) /*const*/
{
	//UNUSED FUNCTION
}

void Shining::StateComponent::Update(const float timeStep)
{
	m_pCurrentState->Update(m_pOwner, timeStep);
}

Shining::StateComponent::~StateComponent()
{
	//need to change this in case I implement shared state pointers
	for (State* pState : m_pStates)
	{
		delete pState;
	}
}