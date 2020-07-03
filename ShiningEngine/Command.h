#pragma once

namespace Shining
{
	class GameObject;

	class Command
	{
	public:
		Command(const unsigned int keyScanCode);
		virtual ~Command() = default;

		virtual void Execute(const Shining::GameObject* pTargetObject) const = 0;
		unsigned int GetKeyScanCode() const;
	protected:
		unsigned int m_AssignedKeyScanCode; //scancode of the key that activates this command
	};
}

