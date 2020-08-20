#include "ShiningEnginePCH.h"
#include "InputContext.h"

Shining::InputContext::InputContext()
	:m_CommandsByVKey{}
	, m_CommandsByControllerInput{}
	, m_ReferenceCount{0}
{
}

Shining::Command* const Shining::InputContext::GetCommand(const unsigned int virtualKey) const noexcept
{
	auto foundIt{ m_CommandsByVKey.find(virtualKey) };

	if (foundIt == m_CommandsByVKey.end())
	{
		return nullptr; //no command associated with this key
	}

	return foundIt->second;
}

const std::map<Shining::ControllerInput, Shining::Command* const>* const Shining::InputContext::GetControllerCommands() const noexcept
{
	return &m_CommandsByControllerInput;
}
Shining::Command* const Shining::InputContext::GetNoInputCommand() const noexcept
{
	return m_pNoInputCommand;
}

Shining::InputContext::~InputContext()
{
	for (auto pair : m_CommandsByVKey)
	{
		if (pair.second != nullptr)
		{
			if (pair.second->DecreaseReferenceCount())
			{
				delete pair.second;
			}
			
		}

	}

	if (m_pNoInputCommand != nullptr)
	{
		if (m_pNoInputCommand->DecreaseReferenceCount())
		{
			delete m_pNoInputCommand;
		}	
	}
}

void Shining::InputContext::AddCommand(Command* pCommandToAdd, const unsigned int virtualKey, const ControllerInput controllerInput) noexcept
{
	m_CommandsByVKey.insert(std::make_pair(virtualKey, pCommandToAdd));
	m_CommandsByControllerInput.insert(std::make_pair(controllerInput, pCommandToAdd));
	pCommandToAdd->IncreaseReferenceCount();
}

void Shining::InputContext::SetNoInputCommand(Command* pCommandToAdd) noexcept
{
	if (m_pNoInputCommand == nullptr)
	{
		m_pNoInputCommand = pCommandToAdd;
	}
	else
	{
		delete m_pNoInputCommand;
		m_pNoInputCommand = pCommandToAdd;
	}
}

void Shining::InputContext::IncreaseReferenceCount() noexcept
{
	++m_ReferenceCount;
}

bool Shining::InputContext::DecreaseReferenceCount() noexcept
{
	--m_ReferenceCount;
	return(m_ReferenceCount <= 0);
}