#include "ShootCommand.h"
#include "ShiningEnginePCH.h"

void ShootCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	//check state, if true:
	if (m_HasShot)
	{
		return;
	}
	Shining::SpawnComponent* const pSpawner{ pTargetObject->GetComponent<Shining::SpawnComponent>() };
	const glm::vec2& ownerPos{ pTargetObject->GetPosition() };

	Shining::PhysicsComponent* const pPhysics{ pTargetObject->GetComponent<Shining::PhysicsComponent>() };
	const glm::vec2& ownerDir{ pPhysics->GetDirection() };
	const glm::vec2 shotSpeed{ 150,150 }; //setting both speeds is fine since the direction is also passed

	const int posOffsetX{ 2 };
	const int posOffsetY{ 4 };
	pSpawner->SpawnObject(ownerPos.x + posOffsetX, ownerPos.y + posOffsetY, shotSpeed, ownerDir);
	//set state to recovering
	const_cast<ShootCommand*>(this)->m_HasShot = true; //really dirty test
}

void ShootCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	//empty
}