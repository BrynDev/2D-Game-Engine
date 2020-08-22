#include "ShiningEnginePCH.h"
#include "StateComponent.h"
#include "State.h"
#include <algorithm>

Shining::StateComponent::StateComponent(State* pStartingState, GameObject* pOwner)
	:Component()
	, m_pStateLayers{}
	, m_pCurrentStates{pStartingState}
	, m_pOwner{pOwner}
	, m_pNextStates{nullptr}
	, m_NeedsSwap{false}
	, m_NeedsSwapVect{false}
{
	std::set<State*> firstLayer{};
	firstLayer.insert(pStartingState);
	m_pStateLayers.push_back(firstLayer);
}

void Shining::StateComponent::Render(const glm::vec2& /*pos*/) /*const*/
{
	//empty
}

void Shining::StateComponent::Update(const float timeStep)
{
	const size_t nrStateLayers{ m_pStateLayers.size() };

	for (size_t i{0}; i < nrStateLayers; ++i)
	{
		m_pCurrentStates[i]->Update(m_pOwner, timeStep);
	}
	//m_pCurrentState->Update(m_pOwner, timeStep);
}

void Shining::StateComponent::SwapBuffer() noexcept
{
	/*if (m_NeedsSwap)
	{
		const size_t nrStateLayers{ m_pStateLayers.size() };
		for (int i{ 0 }; i < nrStateLayers; ++i)
		{
			Shining::State* const pNext{ m_pNextStates[i] };

			if (m_pCurrentStates[i] != pNext)
			{
				m_pCurrentStates[i] = pNext;
				m_pCurrentStates[i]->OnEntry(m_pOwner);
			}		
			
		}
		m_NeedsSwap = false;
	}	*/

	
	const size_t nrStateLayers{ m_pStateLayers.size() };

	for (size_t i{ 0 }; i < nrStateLayers; ++i)
	{
		if (!m_NeedsSwapVect[i]) //check if this layer needs to be swapped
		{
			continue;
		}

		Shining::State* const pNext{ m_pNextStates[i] };
		Shining::State* const pCurrent{ m_pCurrentStates[i] };

		if (pCurrent != pNext) //check if new is different from current
		{
			pCurrent->OnExit(m_pOwner);
			m_pCurrentStates[i] = pNext;
			pNext->OnEntry(m_pOwner);

			m_NeedsSwapVect[i] = false;
		}

	}
}

Shining::State* const Shining::StateComponent::GetCurrentState(const unsigned int layerIdx) const
{
	return m_pCurrentStates.at(layerIdx);
}

void Shining::StateComponent::AddState(State* pStateToAdd, const unsigned int layerIdx)
{
	m_pStateLayers.at(layerIdx).insert(pStateToAdd);
}

void Shining::StateComponent::AddNewStateLayer(State* pStateToAdd) noexcept
{
	std::set<State*> newLayer{};
	newLayer.insert(pStateToAdd);
	m_pStateLayers.push_back(newLayer);
	m_pCurrentStates.push_back(pStateToAdd);
	m_pNextStates.push_back(nullptr);
	m_NeedsSwapVect.push_back(false);
}

Shining::StateComponent::~StateComponent()
{
	const size_t nrStateLayers{ m_pStateLayers.size() };
	for (size_t i{ 0 }; i < nrStateLayers; ++i) //for every layer
	{
		//for every state in this layer
		std::for_each(m_pStateLayers.at(i).begin(), m_pStateLayers.at(i).end(), [](State* pState) {
			delete pState;
			});
		/*const size_t nrStates{ m_pStateLayers.at(i).size };
		for (int j{0}; j < nrStates; ++j)
		{
			m_pStateLayers.at(i).
		}*/
	}

	/*for (State* pState : m_pStates)
	{
		delete pState;
	}*/
}