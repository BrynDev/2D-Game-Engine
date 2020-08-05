#include "IdleState.h"
#include "ObserverEvents.h" //TEST
#include "ShiningEnginePCH.h"

IdleState::IdleState()
	:State()
{
}

void IdleState::Update(Shining::GameObject* const /*pOwner*/, const float /*timeStep*/) noexcept
{
	//empty
}

void IdleState::OnEntry(Shining::GameObject* const /*pOwner*/) noexcept
{
	//unused function
}

void IdleState::OnExit(Shining::GameObject* const pOwner) noexcept
{
	pOwner->NotifyObservers(int(ObservedEvents::gemPickup)); //TEST
	//unused function
}