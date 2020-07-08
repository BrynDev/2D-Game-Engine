#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <set>

namespace Shining
{
	class InputHandler;
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};
	struct Controller
	{
		XINPUT_STATE state{};
		//int id{-1};
		bool isActive{false};
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void CheckForNewControllers();
		bool IsPressed(ControllerButton button) const;
		void RegisterInputHandler(Shining::InputHandler* pHandlerToRegister);
		void UnregisterInputHandler(Shining::InputHandler* pHandlerToUnregister);
		virtual ~InputManager();
	private:
		XINPUT_STATE m_CurrentState{};
		Controller m_Controllers[XUSER_MAX_COUNT]{};
		//ensure that the same handler isn't inserted twice
		std::set<Shining::InputHandler*> m_pInputHandlers{};
		unsigned int m_ControllerCheckTimer{};
	};

}
