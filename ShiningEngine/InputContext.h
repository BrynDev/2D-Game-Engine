#pragma once
#include "InputContext.h"
#include <unordered_map>
#include <map>
#include "ControllerInput.h"

//this class determines which inputs are valid and what each input does per scene

namespace Shining
{
	class Command;

	class InputContext final
	{
	public:
		explicit InputContext();
		~InputContext();
		Command* const GetCommand(const unsigned int virtualKey) const noexcept;
		//Command* const GetCommand(const ControllerInput controllerInput) const noexcept;
		const std::map<ControllerInput, Command* const>* const GetControllerCommands() const noexcept;
		Command* const GetNoInputCommand() const noexcept;
		void AddCommand(Command* pCommandToAdd, const unsigned int virtualKey, const ControllerInput controllerInput) noexcept;
		void SetNoInputCommand(Command* pCommandToAdd) noexcept; //Command to be called when no keys are pressed
		void IncreaseReferenceCount() noexcept;
		bool DecreaseReferenceCount() noexcept;

		InputContext(const InputContext& other) = delete;
		InputContext& operator=(const InputContext& rhs) = delete;
		InputContext(InputContext&& other) = delete;
		InputContext& operator=(InputContext&& rhs) = delete;
	private:
		std::unordered_map<unsigned int, Command* const> m_CommandsByVKey{};
		std::map<ControllerInput, Command* const> m_CommandsByControllerInput{};
		Command* m_pNoInputCommand{ nullptr };
		int m_ReferenceCount;
	};
}

