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

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		void RegisterInputHandler(Shining::InputHandler* pHandlerToRegister);
		void UnregisterInputHandler(Shining::InputHandler* pHandlerToUnregister);
		virtual ~InputManager();
	private:
		XINPUT_STATE m_CurrentState{};
		//ensure that the same handler isn't inserted twice
		std::set<Shining::InputHandler*> m_pInputHandlers;
	};

}
