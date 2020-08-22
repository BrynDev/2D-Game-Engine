#include "ShotCooldownState.h"
#include "ShiningEnginePCH.h"
#include "ShotReadyState.h"

ShotCooldownState::ShotCooldownState()
	:m_CooldownMaxMs{8000} //8 seconds
	, m_TimerMs{0}
{
}

void ShotCooldownState::Update(Shining::GameObject* const pOwner, const float timeStep) noexcept
{
	m_TimerMs += int(timeStep);
	if (m_TimerMs < m_CooldownMaxMs)
	{
		return;
	}

	Shining::StateComponent* const pState{ pOwner->GetComponent<Shining::StateComponent>() };
	pState->ChangeState<ShotReadyState>(1);
}

void ShotCooldownState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::RenderComponent* const pRender{ pOwner->GetComponent<Shining::RenderComponent>() };
	pRender->SetCurrentRow(1, false);
}

void ShotCooldownState::OnExit(Shining::GameObject* const /*pOwner*/) noexcept
{
	m_TimerMs = 0;
}