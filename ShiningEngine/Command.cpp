#include "ShiningEnginePCH.h"
#include "Command.h"

Shining::Command::Command(const unsigned int keyScanCode)
	:m_AssignedKeyScanCode{keyScanCode}
{
}

unsigned int Shining::Command::GetKeyScanCode() const
{
	return m_AssignedKeyScanCode;
}