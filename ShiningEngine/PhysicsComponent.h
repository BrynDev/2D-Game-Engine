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
		void SetSpeedX(const float speedX) noexcept;
		void SetSpeedY(const float speedY) noexcept;
		void SetDirection(const float dirX, const float dirY) noexcept;
		void SetDirectionX(const float dirX) noexcept;
		void SetDirectionY(const float dirY) noexcept;

		const glm::vec2& GetSpeed() const noexcept;
		const glm::vec2& GetDirection() const noexcept;
	private:
		GameObject* m_pOwner;
		glm::vec2 m_Speed;
		glm::vec2 m_Direction;
	};
}


