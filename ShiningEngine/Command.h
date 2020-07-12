#pragma once

namespace Shining
{
	class GameObject;

	class Command
	{
	public:
		Command() = default;
		virtual ~Command() = default;

		virtual void Execute(const Shining::GameObject* pTargetObject) const = 0;
	protected:
	};
}

