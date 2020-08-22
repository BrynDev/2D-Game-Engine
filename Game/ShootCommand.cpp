#include "ShootCommand.h"
#include "ShiningEnginePCH.h"
#include "ShotCooldownState.h"
#include "ShotReadyState.h"

void ShootCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	//check state, if true:
	Shining::StateComponent* pState{ pTargetObject->GetComponent<Shining::StateComponent>() };

	if (pState->IsCurrentState<ShotReadyState>(1)) //check if the current state in layer idx 1 is the ready state
	{
		Shining::PhysicsComponent* const pPhysics{ pTargetObject->GetComponent<Shining::PhysicsComponent>() };
		const glm::vec2& ownerDir{ pPhysics->GetDirection() };
		const glm::vec2 shotSpeed{ 150,150 }; //setting both speeds is fine since a direction is also passed, either x or y will be zero

		const int posOffsetX{ 2 }; //center the fireball to the character better
		const int posOffsetY{ 4 };

		const glm::vec2& ownerPos{ pTargetObject->GetPosition() };
		Shining::SpawnComponent* const pSpawner{ pTargetObject->GetComponent<Shining::SpawnComponent>() };
		pSpawner->SpawnObject(ownerPos.x + posOffsetX, ownerPos.y + posOffsetY, shotSpeed, ownerDir); //spawn the fireball
		
		pState->ChangeState<ShotCooldownState>(1); //set state in layer idx 1 to cooldown

		Shining::AudioPlayer::GetInstance().PlaySoundEffect("ShotSound.wav");
	}
	
}

void ShootCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	//empty
}