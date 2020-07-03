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

	return true;
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
