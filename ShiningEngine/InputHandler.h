#pragma once
#include <vector>

namespace Shining
{
	class Command;
	class GameObject;

	class InputHandler final
	{
	public:
		InputHandler(Shining::GameObject* const pObjectToControl);
		~InputHandler();

		void HandleInput(const unsigned int keyDownScanCode) const noexcept;
		void AddCommand(const Shining::Command* pCommandToAdd);

		InputHandler(const InputHandler& other) = delete;
		InputHandler(InputHandler&& other) = delete;
		InputHandler& operator=(const InputHandler& other) = delete;
		InputHandler& operator=(InputHandler&& other) = delete;
	private:
		std::vector<const Shining::Command*> m_pCommands;
		Shining::GameObject* const m_pObjectToControl;
	};
}


