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
	if (m_pNoInputCommand != nullptr)
	{
		delete m_pNoInputCommand;
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
					m_pNoInputCommand->Execute(m_pPlayerCharacter); //if no relevant buttons are currently down, execute the NoInputCommand
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
	for (int i{0}; i < XUSER_MAX_COUNT; ++i)
	{
		Controller controller{ m_Controllers[i] };
		if (!controller.isActive)
		{
			continue; //this controller isn't being used
		}

		XInputGetState(i, &controller.gamepadState);		
		XINPUT_GAMEPAD gamepad{ controller.gamepadState.Gamepad };

		for (std::pair<ControllerInput, Command*> pair : m_CommandsByControllerInput)
		{
			auto foundIt{ m_CurrentControllerInputs.find(pair.first) }; //is this button being held?
			if (foundIt != m_CurrentControllerInputs.end())
			{
				//this button was pressed last frame, is it currently still pressed?
				if (IsControllerInputPressed(gamepad, pair.first))
				{
					//the button is still being held
					continue;
				}
				else
				{
					//the button has been released
					m_CurrentControllerInputs.erase(pair.first);
					pair.second->OnRelease(m_pPlayerCharacter);
					if (m_CurrentControllerInputs.empty())
					{
						//if no buttons are being held, execute the NoInputCommand
						m_pNoInputCommand->Execute(m_pPlayerCharacter);
					}
				}
			}
			else if (IsControllerInputPressed(gamepad, pair.first)) //did the button just start being pressed?
			{
				pair.second->Execute(m_pPlayerCharacter);
				m_CurrentControllerInputs.insert(pair.first);
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

bool Shining::InputManager::IsControllerInputPressed(const XINPUT_GAMEPAD& gamepad, const ControllerInput input) const noexcept
{
	bool isPressed{ false };
	//I use these next 2 values to more accurately check the stick position, this makes the game feel nicer to control
	const float normalizedStickThreshold{ 0.5f };
	const float thumbstickMax{ 32767.f }; //value defined by XINPUT, source:https://docs.microsoft.com/en-us/windows/win32/api/xinput/ns-xinput-xinput_gamepad

	//=========
	//BUTTONS & TRIGGERS
	//=========
	switch (input)
	{
	case ControllerInput::ButtonA:
		if (gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::ButtonB:
		if (gamepad.wButtons & XINPUT_GAMEPAD_B)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::ButtonX:
		if (gamepad.wButtons & XINPUT_GAMEPAD_X)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::ButtonY:
		if (gamepad.wButtons & XINPUT_GAMEPAD_Y)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::DPadUp:
		if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::DPadRight:
		if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::DPadDown:
		if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::DPadLeft:
		if (gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::LeftBumper:
		if (gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::RightBumper:
		if (gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::LeftTrigger:
		if (gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::RightTrigger:
		if (gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::Select:
		if (gamepad.wButtons & XINPUT_GAMEPAD_BACK)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::Start:
		if (gamepad.wButtons & XINPUT_GAMEPAD_START)
		{
			isPressed = true;
		}
		break;
		//=========
		//STICKS
		//=========
	case ControllerInput::LeftStickUp:
		if (gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && (abs(gamepad.sThumbLX) / thumbstickMax) < normalizedStickThreshold)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::LeftStickRight:
		if (gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && (abs(gamepad.sThumbLY) / thumbstickMax) < normalizedStickThreshold)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::LeftStickDown:
		if (gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && (abs(gamepad.sThumbLX) / thumbstickMax) < normalizedStickThreshold)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::LeftStickLeft:
		if (gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && (abs(gamepad.sThumbLY) / thumbstickMax) < normalizedStickThreshold)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::RightStickUp:
		if (gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && (abs(gamepad.sThumbRX) / thumbstickMax) < normalizedStickThreshold)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::RightStickRight:
		if (gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && (abs(gamepad.sThumbRY) / thumbstickMax) < normalizedStickThreshold)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::RightStickDown:
		if (gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && (abs(gamepad.sThumbRX) / thumbstickMax) < normalizedStickThreshold)
		{
			isPressed = true;
		}
		break;
	case ControllerInput::RightStickLeft:
		if (gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && (abs(gamepad.sThumbRY) / thumbstickMax) < normalizedStickThreshold)
		{
			isPressed = true;
		}
		break;
	default:
		break;
	}

	return isPressed;
}

void Shining::InputManager::AddCommand(Command* pCommandToAdd, const unsigned int virtualKey, const ControllerInput controllerInput)
{
	m_CommandsByVKey.insert(std::make_pair(virtualKey, pCommandToAdd));
	m_CommandsByControllerInput.insert(std::make_pair(controllerInput, pCommandToAdd));
}

void Shining::InputManager::SetNoInputCommand(Command* pCommandToAdd) noexcept
{
	if (m_pNoInputCommand == nullptr)
	{
		m_pNoInputCommand = pCommandToAdd;
	}
	else
	{
		delete m_pNoInputCommand;
		m_pNoInputCommand = pCommandToAdd;
	}
}

void Shining::InputManager::RegisterPlayerCharacter(GameObject* pCharacterToControl)
{
	m_pPlayerCharacter = pCharacterToControl;
}
