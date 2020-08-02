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
	if (m_pNoKeysCommand != nullptr)
	{
		delete m_pNoKeysCommand;
	}
	
}

bool Shining::InputManager::ProcessInput()
{
	//============
	//KEYBOARD
	//============
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		
		if (e.type == SDL_KEYDOWN) //if the button is pressed, execute command
		{
			auto foundIt{ m_CommandsByVKey.find(e.key.keysym.sym) }; //is this button relevant, does it have an associated command?

			if (foundIt != m_CommandsByVKey.end())
			{
				foundIt->second->Execute(m_pPlayerCharacter);
				m_CurrentlyPressedKeys.insert(e.key.keysym.sym);
			}
			
		}

		if (e.type == SDL_KEYUP) //if the button is released, cancel the command
		{
			auto foundIt{ m_CommandsByVKey.find(e.key.keysym.sym) };

			if (foundIt != m_CommandsByVKey.end())
			{
				foundIt->second->OnRelease(m_pPlayerCharacter);

				m_CurrentlyPressedKeys.erase(e.key.keysym.sym);
				if (m_CurrentlyPressedKeys.empty())
				{
					m_pNoKeysCommand->Execute(m_pPlayerCharacter); //if no relevant buttons are currently down, execute the NoKeysCommand
				}
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
			XInputGetState(i, &controller.gamepadState);		
			XINPUT_GAMEPAD gamepad{ controller.gamepadState.Gamepad };
			XINPUT_GAMEPAD prevGamepad{ controller.prevGamepadState.Gamepad };

			for (std::pair<ControllerInput, Command*> pair : m_CommandsByControllerInput)
			{
				bool wasPressedPrevFrame{ false };
				switch (pair.first)
				{
				//=========
				//BUTTONS
				//=========
				case ControllerInput::ButtonA:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_A) //was this button pressed previous frame?
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_A) //is this button currently being pressed?
					{
						if (wasPressedPrevFrame)
						{
							continue; //button is being held down, no need to execute the command again
						}
						else //button was newly pressed this frame, execute command
						{
							pair.second->Execute(m_pPlayerCharacter); 
						}
					}
					else if (wasPressedPrevFrame) //button was released this frame, stop the command
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::ButtonB:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_B)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_B)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::ButtonX:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_X)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_X)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::ButtonY:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_Y)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_Y)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::DPadUp:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::DPadRight:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::DPadDown:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::DPadLeft:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::LeftBumper:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::RightBumper:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::LeftTrigger:
					if (prevGamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
					{
						wasPressedPrevFrame = true;
					}

					if (prevGamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::RightTrigger:
					if (prevGamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
					{
						wasPressedPrevFrame = true;
					}

					if (prevGamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::Select:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_BACK)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_BACK)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::Start:
					if (prevGamepad.wButtons & XINPUT_GAMEPAD_START)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.wButtons & XINPUT_GAMEPAD_START)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				//=========
				//STICKS
				//=========
				case ControllerInput::LeftStickUp:
					if (prevGamepad.sThumbLY > thumbStickDeadZone)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.sThumbLY > thumbStickDeadZone)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::LeftStickRight:
					if (prevGamepad.sThumbLX > thumbStickDeadZone)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.sThumbLX > thumbStickDeadZone)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::LeftStickDown:
					if (prevGamepad.sThumbLY < -thumbStickDeadZone)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.sThumbLY < -thumbStickDeadZone)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::LeftStickLeft:
					if (prevGamepad.sThumbLX < -thumbStickDeadZone)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.sThumbLX < -thumbStickDeadZone)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::RightStickUp:
					if (prevGamepad.sThumbRY > thumbStickDeadZone)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.sThumbRY > thumbStickDeadZone)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::RightStickRight:
					if (prevGamepad.sThumbRX > thumbStickDeadZone)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.sThumbRX > thumbStickDeadZone)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::RightStickDown:
					if (prevGamepad.sThumbRY < -thumbStickDeadZone)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.sThumbRY < -thumbStickDeadZone)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				case ControllerInput::RightStickLeft:
					if (prevGamepad.sThumbRX < -thumbStickDeadZone)
					{
						wasPressedPrevFrame = true;
					}

					if (gamepad.sThumbRX < -thumbStickDeadZone)
					{
						if (wasPressedPrevFrame)
						{
							continue;
						}
						else
						{
							pair.second->Execute(m_pPlayerCharacter);
						}
					}
					else if (wasPressedPrevFrame)
					{
						pair.second->OnRelease(m_pPlayerCharacter);
					}
					break;
				default:
					break;
				}	
			}	

			m_Controllers[i].prevGamepadState = controller.gamepadState; //update prevGamepadState of this controller
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
	
	for (int i{0}; i < XUSER_MAX_COUNT; ++i)
	{
		//check all controller ports
		DWORD dwordResult{};
		dwordResult = XInputGetState(i, &m_Controllers[i].gamepadState);
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

void Shining::InputManager::SetNoKeysCommand(Command* pCommandToAdd) noexcept
{
	if (m_pNoKeysCommand == nullptr)
	{
		m_pNoKeysCommand = pCommandToAdd;
	}
	else
	{
		delete m_pNoKeysCommand;
		m_pNoKeysCommand = pCommandToAdd;
	}
}

void Shining::InputManager::RegisterPlayerCharacter(GameObject* pCharacterToControl)
{
	m_pPlayerCharacter = pCharacterToControl;
}
