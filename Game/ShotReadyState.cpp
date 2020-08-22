#include "ShotReadyState.h"
#include "ShiningEnginePCH.h"

void ShotReadyState::Update(Shining::GameObject* const /*pOwner*/, const float /*timeStep*/) noexcept
{
	//empty
}

void ShotReadyState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::RenderComponent* const pRender{ pOwner->GetComponent<Shining::RenderComponent>() };
	pRender->SetCurrentRow(0, false);
}

void ShotReadyState::OnExit(Shining::GameObject* const /*pOwner*/) noexcept
{
	//empty
}