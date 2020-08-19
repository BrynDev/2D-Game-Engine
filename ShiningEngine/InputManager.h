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
		void SetInputContext(InputContext* const pContext) noexcept;
		void RegisterPlayerCharacter(GameObject* pCharacterToControl);

		virtual ~InputManager() = default;
	private:
		InputContext* m_pCurrentInputContext{};

		Controller m_Controllers[XUSER_MAX_COUNT]{};
		GameObject* m_pPlayerCharacter{nullptr};
		std::unordered_set<unsigned int> m_CurrentlyPressedKeys{}; //use a set because I want the elements to be unique
		std::unordered_set<ControllerInput> m_CurrentControllerInputs{};
		float m_ControllerCheckTimer{};

		bool IsControllerInputPressed(const XINPUT_GAMEPAD& gamepad, const ControllerInput input) const noexcept;
	};

}
