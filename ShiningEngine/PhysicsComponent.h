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
		virtual void SwapBuffer() noexcept override;
		void MoveOwner(const float timeStep) noexcept;
		//void MoveBackwards()
		void SetSpeed(const float speedX, const float speedY) noexcept;
		void SetSpeedX(const float speedX) noexcept;
		void SetSpeedY(const float speedY) noexcept;
		void SetDirection(const float dirX, const float dirY) noexcept;
		void SetDirectionX(const float dirX) noexcept;
		void SetDirectionY(const float dirY) noexcept;

		const glm::vec2& GetSpeed() const noexcept;
		const glm::vec2& GetDirection() const noexcept;
	private:
		struct MoveInfo
		{
			glm::vec2 speed;
			glm::vec2 direction;
		};
		MoveInfo m_MoveInfo[2]; //used for double buffered update, I know I only need 2
		GameObject* const m_pOwner;
		MoveInfo* m_pNextMoveInfo;
		MoveInfo* m_pCurrentMoveInfo;
		//glm::vec2 m_Speed;
		//glm::vec2 m_Direction;
		bool m_NeedsSwap;
	};
}


