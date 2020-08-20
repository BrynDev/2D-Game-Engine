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
		void SetPlayer(GameObject* const pObjectToControl);
		void SetKeyboardPlayer(GameObject* const pObjectToControl);
		void SetControllerPlayer(GameObject* const pObjectToControl);

		virtual ~InputManager() = default;
	private:	
		Controller m_Controllers[XUSER_MAX_COUNT]{};

		InputContext* m_pCurrentInputContext{};
		GameObject m_NullObject{0,0};
		GameObject* m_pPlayerCharacterKeyboard{&m_NullObject};
		GameObject* m_pPlayerCharacterController{ &m_NullObject };
		std::unordered_set<unsigned int> m_CurrentlyPressedKeys{}; //use a set because I want the elements to be unique
		std::unordered_set<ControllerInput> m_CurrentControllerInputs{};
		float m_ControllerCheckTimer{};

		bool IsControllerInputPressed(const XINPUT_GAMEPAD& gamepad, const ControllerInput input) const noexcept;
	};

}
