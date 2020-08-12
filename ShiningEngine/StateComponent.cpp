#include "ShiningEnginePCH.h"
#include "StateComponent.h"
#include "State.h"

Shining::StateComponent::StateComponent(State* pStartingState, GameObject* pOwner)
	:Component()
	, m_pCurrentState{pStartingState}
	, m_pOwner{pOwner}
	, m_pNextState{nullptr}
{
	m_pStates.insert(pStartingState);
}

void Shining::StateComponent::Render(const glm::vec2& /*pos*/) /*const*/
{
	//UNUSED FUNCTION
}

void Shining::StateComponent::Update(const float timeStep)
{
	/*if (m_pNextState != nullptr)
	{
		//TEMP
		m_pCurrentState->OnExit(m_pOwner);
		m_pCurrentState = m_pNextState;
		m_pCurrentState->OnEntry(m_pOwner, glm::vec4{0,0,0,0});
		m_pNextState = nullptr;
	}*/
	m_pCurrentState->Update(m_pOwner, timeStep);
}

void Shining::StateComponent::SwapBuffer() noexcept
{
	if (m_NeedsSwap)
	{
		m_pCurrentState = m_pNextState;
		m_pCurrentState->OnEntry(m_pOwner);
		m_NeedsSwap = false;
	}	
}

void Shining::StateComponent::AddState(State* pStateToAdd) noexcept
{
	m_pStates.insert(pStateToAdd);
}

Shining::StateComponent::~StateComponent()
{
	//need to change this in case I implement shared state pointers
	for (State* pState : m_pStates)
	{
		delete pState;
	}
}