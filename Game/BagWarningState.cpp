#include "BagWarningState.h"
#include "BagFallingState.h"
#include "ShiningEnginePCH.h"

BagWarningState::BagWarningState()
	:State()
	, m_FallDelayTimerMs{0}
{
}

void BagWarningState::Update(Shining::GameObject* const pOwner, const float timeStep) noexcept
{
	m_FallDelayTimerMs += int(timeStep);
	const int fallDelayMs{ 1000 };
	if (m_FallDelayTimerMs > fallDelayMs)
	{
		Shining::StateComponent* pState{ pOwner->GetComponent<Shining::StateComponent>() };
		pState->ChangeState<BagFallingState>();
	}
}
void BagWarningState::OnEntry(Shining::GameObject* const /*pOwner*/) noexcept
{
	Shining::AudioPlayer::GetInstance().PlaySoundEffect("BagFallWarningSound.wav");
}
void BagWarningState::OnExit(Shining::GameObject* const /*pOwner*/) noexcept
{
	m_FallDelayTimerMs = 0;
}