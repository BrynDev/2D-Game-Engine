#pragma once
#include "Component.h"

namespace Shining
{
	class StateComponent final : public Component
	{
	public:
		StateComponent();
		virtual ~StateComponent() = default;
		virtual void Render(const glm::vec3& pos) /*const*/ override;
		virtual void Update(const float timeStep) override;
	private:
	};
}


