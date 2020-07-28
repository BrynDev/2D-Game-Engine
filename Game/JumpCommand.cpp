#include "JumpCommand.h"
#include "GameObject.h"
//TEMP
#include <iostream>


void JumpCommand::Execute( Shining::GameObject* const /*pTargetObject*/) const noexcept
{
	std::cout << "Command called\n";
	//pTargetObject->GetComponent<physics>()->jump;
	//pTargetObject->Jump();
}