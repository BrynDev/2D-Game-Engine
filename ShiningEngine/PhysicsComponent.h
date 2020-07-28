#pragma once
#include "Component.h"

namespace Shining
{
	class GameObject;

	class PhysicsComponent final : public Component
	{
	public:
		PhysicsComponent(GameObject* const pOwner);
		virtual ~PhysicsComponent() = default;

		virtual void Update(const float timeStep) noexcept override;
		virtual void Render(const glm::vec2& pos) /*const*/ noexcept override;
		void MoveOwner(const float timeStep) noexcept;
		void SetSpeed(const float speedX, const float speedY) noexcept;
		void SetDirection(const float dirX, const float dirY) noexcept;
	private:
		GameObject* m_pOwner;
		glm::vec2 m_Speed;
		glm::vec2 m_Direction;
	};
}


