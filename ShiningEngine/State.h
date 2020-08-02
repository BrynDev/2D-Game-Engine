#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec4.hpp>
#pragma warning(pop)

namespace Shining
{
	class GameObject;

	class State
	{
	public:
		State() = default;
		virtual ~State() = default;

		virtual void Update(GameObject* const pOwner, const float timeStep) noexcept = 0;
		//data variable used to optionally pass additional information in, left to the user
		virtual void OnEntry(GameObject* const pOwner) noexcept = 0;
		virtual void OnExit(GameObject* const pOwner) noexcept = 0;
		
	};
}