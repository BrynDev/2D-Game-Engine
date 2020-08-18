#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <map>
#include <unordered_map>
#include <unordered_set>
#include "GameObject.h"
#include "ControllerInput.h"

namespace Shining
{
	class InputContext;
	
	struct Controller
	{
		XINPUT_STATE gamepadState{};
		bool isActive{false};
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void CheckForNewControllers(const float deltaTime) noexcept;
		//void AddCommand(Command* pCommandToAdd, const unsigned int virtualKey, const ControllerInput controllerInput);
		void SetInputContext(InputContext* const pContext) noexcept;
		//void SetNoInputCommand(Command* pCommandToAdd) noexcept; //Command to be called when no keys are pressed

		void RegisterPlayerCharacter(GameObject* pCharacterToControl);

		virtual ~InputManager();
	private:
		//TEST
		//std::vector<InputContext* const> m_pInputContexts{};
		InputContext* m_pCurrentInputContext{};

		Controller m_Controllers[XUSER_MAX_COUNT]{};
		GameObject* m_pPlayerCharacter{nullptr};
		std::unordered_map<unsigned int, Command* const> m_CommandsByVKey{};
		std::map<ControllerInput, Command* const> m_CommandsByControllerInput{};
		std::unordered_set<unsigned int> m_CurrentlyPressedKeys{}; //use a set because I want the elements to be unique
		std::unordered_set<ControllerInput> m_CurrentControllerInputs{};
		Command* m_pNoInputCommand{nullptr};
		float m_ControllerCheckTimer{};

		bool IsControllerInputPressed(const XINPUT_GAMEPAD& gamepad, const ControllerInput input) const noexcept;
	};

}
