#include "MoveUpCommand.h"
#include "ShiningEnginePCH.h"
#include "MoveState.h"
#include "IdleState.h"


MoveUpCommand::MoveUpCommand()
	:Command()
{
}

void MoveUpCommand::Execute(Shining::GameObject* const pTargetObject) const noexcept
{
	Shining::PhysicsComponent* pPhysics{ pTargetObject->GetComponent<Shining::PhysicsComponent>() };
	//pPhysics->SetSpeed(0, 150);
	pPhysics->SetDirection(0, -1);
	pTargetObject->GetComponent<Shining::StateComponent>()->ChangeState<MoveState>();

	Shining::RenderComponent* pRender{ pTargetObject->GetComponent<Shining::RenderComponent>() };
	float rotationAngle{ -90.f };
	rotationAngle *= (int(pRender->GetFlipFlag() != Shining::RenderFlipFlag::horizontal) * 2) - 1; //-1 if false, 1 if true;
	pRender->SetRotationAngle(rotationAngle);

	//Above line replaces the following if branch:

	/*const Shining::RenderFlipFlag flipFlag{ pRender->GetFlipFlag() };
	if (flipFlag == Shining::RenderFlipFlag::horizontal)
	{
		pRender->SetRotationAngle(90.f);
	}
	else
	{
		pRender->SetRotationAngle(-90.f);
	}*/
}

void MoveUpCommand::OnRelease(Shining::GameObject* const /*pTargetObject*/) const noexcept
{
}