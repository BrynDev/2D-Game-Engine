#include "JumpCommand.h"
#include "GameObject.h"
//TEMP
#include <iostream>

JumpCommand::JumpCommand(const unsigned int keyScanCode)
	:Command(keyScanCode)
{
}

void JumpCommand::Execute(const Shining::GameObject* /*pTargetObject*/) const
{
	std::cout << "Command called\n";
	//pTargetObject->GetComponent<physics>()->jump;
	//pTargetObject->Jump();
}