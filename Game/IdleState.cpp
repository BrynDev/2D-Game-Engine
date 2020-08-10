#include "IdleState.h"
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
	//empty
	
}

void IdleState::OnExit(Shining::GameObject* const /*pOwner*/) noexcept
{
	//empty
}