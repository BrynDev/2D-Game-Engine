#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include <unordered_map>
#include "GameObject.h"
#include "ControllerInput.h"

namespace Shining
{
	class InputHandler;
	
	struct Controller
	{
		XINPUT_STATE state{};
		bool isActive{false};
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddCommand(Command* pCommandToAdd, const unsigned int virtualKey, const ControllerInput controllerInput);
		void RegisterPlayerCharacter(GameObject* pCharacterToControl);
		virtual ~InputManager();
	private:
		void CheckForNewControllers();

		XINPUT_STATE m_CurrentState{};
		Controller m_Controllers[XUSER_MAX_COUNT]{};
		GameObject* m_pPlayerCharacter;
		std::unordered_map<unsigned int, Command*> m_CommandsByVKey{};
		std::map<ControllerInput, Command*> m_CommandsByControllerInput{};
		unsigned int m_ControllerCheckTimer{};
	};

}
