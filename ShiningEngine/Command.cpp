#include "ShiningEnginePCH.h"
#include "Command.h"

Shining::Command::Command()
	:m_ReferenceCount{0}
{
}

void Shining::Command::IncreaseReferenceCount() noexcept
{
	++m_ReferenceCount;
}

bool Shining::Command::DecreaseReferenceCount() noexcept
{
	--m_ReferenceCount;
	return (m_ReferenceCount <= 0);
}
