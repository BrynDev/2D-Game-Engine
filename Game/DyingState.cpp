#include "DyingState.h"
#include "ShiningEnginePCH.h"
#include "IdleState.h"

DyingState::DyingState()
	:State()
	, m_DyingTimer{0}
{
}

void DyingState::Update(Shining::GameObject* const pOwner, const float timeStep) noexcept
{
	m_DyingTimer += int(timeStep);
	const int maxDyingTime{ 4000 }; //4 seconds
	if (m_DyingTimer >= maxDyingTime)
	{
		Shining::StateComponent* const pState{ pOwner->GetComponent<Shining::StateComponent>() };
		pState->ChangeState<IdleState>();
		Shining::SceneManager::GetInstance().ResetCurrentScene();
	}
	
}

void DyingState::OnEntry(Shining::GameObject* const pOwner) noexcept
{
	Shining::RenderComponent* const pRender{ pOwner->GetComponent<Shining::RenderComponent>() };
	pRender->SetCurrentRow(2, true);
	pRender->SetRotationAngle(0);
	pRender->SetFlipFlag(Shining::RenderFlipFlag::none);
	
	Shining::PhysicsComponent* const pPhysics{ pOwner->GetComponent<Shining::PhysicsComponent>() };
	pPhysics->SetIsMoving(false); //make sure the player stops moving

	Shining::AudioPlayer& audio{ Shining::AudioPlayer::GetInstance() };
	audio.StopAllEffects();
	audio.PlayMusic("PlayerDeathSound.wav", 1);
	//play music instead
}

void DyingState::OnExit(Shining::GameObject* const pOwner) noexcept
{
	m_DyingTimer = 0;
	Shining::RenderComponent* const pRender{ pOwner->GetComponent<Shining::RenderComponent>() };
	pRender->SetCurrentRow(0, false);
}