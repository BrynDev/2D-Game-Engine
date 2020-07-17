#include "ShiningEnginePCH.h"
#include "InputManager.h"
#include <SDL.h>
#include <algorithm>

Shining::InputManager::~InputManager()
{
	for (auto pair : m_CommandsByVKey)
	{
		if (pair.second != nullptr)
		{
			delete pair.second;
			pair.second = nullptr;
		}
		
	}
	/*for (auto pair : m_CommandsByControllerInput)
	{
		if (pair.second != nullptr)
		{
			delete pair.second;
			pair.second = nullptr;
		}

	}*/
}

bool Shining::InputManager::ProcessInput()
{
	//============
	//KEYBOARD
	//============
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			auto foundIt{ m_CommandsByVKey.find(e.key.keysym.sym) };
			
			if (foundIt != m_CommandsByVKey.end())
			{
				foundIt->second->Execute(m_pPlayerCharacter);
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			//to add later
		}
	}


	//============
	//CONTROLLER
	//============
	const int thumbStickDeadZone{ 12000 };
	for (int i{0}; i < XUSER_MAX_COUNT; ++i)
	{
		Controller controller{ m_Controllers[i] };
		if (controller.isActive)
		{

			XInputGetState(i, &controller.state);
		
				XINPUT_GAMEPAD gamepadState{ controller.state.Gamepad };
				//controller state has changed, check for details
				for (std::pair<ControllerInput, Command*> pair : m_CommandsByControllerInput)
				{
					switch (pair.first)
					{
					//=========
					//BUTTONS
					//=========
					case ControllerInput::ButtonA:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_A)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::ButtonB:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_B)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::ButtonX:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_X)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::ButtonY:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_Y)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::DPadUp:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_DPAD_UP)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::DPadRight:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::DPadDown:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break; 
					case ControllerInput::DPadLeft:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::LeftBumper:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::RightBumper:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::LeftTrigger:
						if (gamepadState.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::RightTrigger:
						if (gamepadState.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::Select:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_BACK)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::Start:
						if (gamepadState.wButtons & XINPUT_GAMEPAD_START)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					//=========
					//STICKS
					//=========
					case ControllerInput::LeftStickUp:
						if (gamepadState.sThumbLY > thumbStickDeadZone)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::LeftStickRight:
						if (gamepadState.sThumbLX > thumbStickDeadZone)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::LeftStickDown:
						if (gamepadState.sThumbLY < -thumbStickDeadZone)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::LeftStickLeft:
						if (gamepadState.sThumbLX < -thumbStickDeadZone)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::RightStickUp:
						if (gamepadState.sThumbRY > thumbStickDeadZone)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::RightStickRight:
						if (gamepadState.sThumbRX > thumbStickDeadZone)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::RightStickDown:
						if (gamepadState.sThumbRY < -thumbStickDeadZone)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					case ControllerInput::RightStickLeft:
						if (gamepadState.sThumbRX < -thumbStickDeadZone)
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
						break;
					default:
						//return to neutral state?
						break;
					}
				}
				
				
			}
	}
	return true;
}

//"For performance reasons, don't call XInputGetState for an 'empty' user slot every frame. 
//We recommend that you space out checks for new controllers every few seconds instead."
//from https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput#multiple-controllers
void Shining::InputManager::CheckForNewControllers(const float deltaTime) noexcept
{
	m_ControllerCheckTimer += deltaTime;
	if (m_ControllerCheckTimer <= 5000) //5 seconds
	{
		return; //early exit
	}
	m_ControllerCheckTimer = 0;
	
	for (int i{}; i < XUSER_MAX_COUNT; ++i)
	{
		//check all controller ports
		DWORD dwordResult{};
		dwordResult = XInputGetState(i, &m_Controllers[i].state);
		if (dwordResult == ERROR_SUCCESS)
		{
			//controller is connected in this port
			m_Controllers[i].isActive = true;
		}
		else
		{
			//no controller connected in this port
			m_Controllers[i].isActive = false;
		}
	}
}

void Shining::InputManager::AddCommand(Command* pCommandToAdd, const unsigned int virtualKey, const ControllerInput controllerInput)
{
	m_CommandsByVKey.insert(std::make_pair(virtualKey, pCommandToAdd));
	m_CommandsByControllerInput.insert(std::make_pair(controllerInput, pCommandToAdd));
}

void Shining::InputManager::RegisterPlayerCharacter(GameObject* pCharacterToControl)
{
	m_pPlayerCharacter = pCharacterToControl;
}
