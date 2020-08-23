#include "ShootCommand.h"
#include "ShiningEnginePCH.h"
#include "ShotCooldownState.h"
#include "ShotReadyState.h"
#include "DyingState.h"

void ShootCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	Shining::StateComponent* const pState{ pTargetObject->GetComponent<Shining::StateComponent>() };
	if (!pState->IsCurrentState<DyingState>()) //block inputs if the player is dying
	{
		//check state, if true:
		const int stateLayerIdx{ 1 };

		if (pState->IsCurrentState<ShotReadyState>(stateLayerIdx)) //check if the current state in layer idx 1 is the ready state
		{
			Shining::PhysicsComponent* const pPhysics{ pTargetObject->GetComponent<Shining::PhysicsComponent>() };
			const glm::vec2& ownerDir{ pPhysics->GetDirection() };
			const glm::vec2 shotSpeed{ 180,180 }; //setting both speeds is fine since a direction is also passed, either x or y will be zero

			const int posOffsetX{ 2 }; //center the fireball to the character better
			const int posOffsetY{ 4 };

			const glm::vec2& ownerPos{ pTargetObject->GetPosition() };
			Shining::SpawnComponent* const pSpawner{ pTargetObject->GetComponent<Shining::SpawnComponent>() };
			pSpawner->SpawnObject(ownerPos.x + posOffsetX, ownerPos.y + posOffsetY, shotSpeed, ownerDir); //spawn the fireball

			pState->ChangeState<ShotCooldownState>(stateLayerIdx); //set state in layer idx 1 to cooldown

			Shining::AudioPlayer::GetInstance().PlaySoundEffect("ShotSound.wav");
		}
	}
	
	
}

void ShootCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	//empty
}