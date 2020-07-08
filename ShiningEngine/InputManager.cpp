#include "ShiningEnginePCH.h"
#include "InputManager.h"
#include <SDL.h>
#include <algorithm>
#include "InputHandler.h"

Shining::InputManager::~InputManager()
{
	for (Shining::InputHandler* pHandler : m_pInputHandlers)
	{
		delete pHandler;
	}
}

bool Shining::InputManager::ProcessInput()
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);
	++m_ControllerCheckTimer;
	if (m_ControllerCheckTimer > 500)
	{
		CheckForNewControllers();
		m_ControllerCheckTimer = 0;
	}
	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) 
		{
			for (Shining::InputHandler* pHandler : m_pInputHandlers)
			{
				pHandler->HandleInput(e.key.keysym.scancode);
			}			
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			//to add later
		}
	}
	
	for (int i{0}; i < XUSER_MAX_COUNT; ++i)
	{
		Controller controller{ m_Controllers[i] };
		if (controller.isActive)
		{
			DWORD firstPacketNumber{ controller.state.dwPacketNumber };
			XInputGetState(i, &controller.state);
			DWORD secondPacketNumber{ controller.state.dwPacketNumber };

			if (firstPacketNumber != secondPacketNumber)
			{
				//controller state has changed, check for details
				const int thumbStickDeadZone{ 12000 };
				//sticks
				if (controller.state.Gamepad.sThumbLY > thumbStickDeadZone)
				{
					//move up
					std::cout << "up; y value: " << controller.state.Gamepad.sThumbLY << '\n';
				}
				if (controller.state.Gamepad.sThumbLY < -thumbStickDeadZone)
				{
					//move down
					std::cout << "down; y value: " << controller.state.Gamepad.sThumbLY << '\n';
				}
			}
		}
	}



	return true;
}

//"For performance reasons, don't call XInputGetState for an 'empty' user slot every frame. 
//We recommend that you space out checks for new controllers every few seconds instead."
//from https://docs.microsoft.com/en-us/windows/win32/xinput/getting-started-with-xinput#multiple-controllers
void Shining::InputManager::CheckForNewControllers()
{
	for (int i{}; i < XUSER_MAX_COUNT; ++i)
	{
		DWORD dwordResult{};
		dwordResult = XInputGetState(i, &m_Controllers[i].state);
		if (dwordResult == ERROR_SUCCESS)
		{
			m_Controllers[i].isActive = true;		
		}
		else
		{
			m_Controllers[i].isActive = false;
		}
	}
}

bool Shining::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

void Shining::InputManager::RegisterInputHandler(Shining::InputHandler* pHandlerToAdd)
{
	m_pInputHandlers.insert(pHandlerToAdd);
}

void Shining::InputManager::UnregisterInputHandler(Shining::InputHandler* pHandlerToUnregister)
{
	const std::set<Shining::InputHandler*>::iterator foundIt{ std::find(m_pInputHandlers.begin(), m_pInputHandlers.end(), pHandlerToUnregister) };

	if (foundIt == m_pInputHandlers.end())
	{
		//Handler not found
		return;
	}

	//m_pInputHandlers.erase(std::remove(m_pInputHandlers.begin(), m_pInputHandlers.end(), pHandlerToUnregister), m_pInputHandlers.end());

	//set erase decreases the physical size of the set, no need to call remove
	m_pInputHandlers.erase(foundIt);
}
