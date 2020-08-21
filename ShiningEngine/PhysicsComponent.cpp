#include "ShiningEnginePCH.h"
#include "PhysicsComponent.h"


Shining::PhysicsComponent::PhysicsComponent(GameObject* const pOwner, const bool isCurrentlyMoving)
	:m_pOwner{pOwner}
	, m_NeedsSwap{false}
	, m_IsMoving{isCurrentlyMoving}
	, m_IsMovingNext{isCurrentlyMoving}
{
	m_MoveInfo[0] = MoveInfo{};
	m_MoveInfo[1] = MoveInfo{};
	m_pCurrentMoveInfo = &m_MoveInfo[0];
	m_pNextMoveInfo = &m_MoveInfo[1];
}

void Shining::PhysicsComponent::Render(const glm::vec2& /*pos*/) /*const*/ noexcept
{
	//unused
}

void Shining::PhysicsComponent::Update(const float timeStep) noexcept
{
	//relevant updates are executed in the state object instead
	if (m_IsMoving)
	{
		const glm::vec2& oldPos{ m_pOwner->GetPosition() };
		const glm::vec2& direction{ m_pCurrentMoveInfo->direction };
		const glm::vec2& speed{ m_pCurrentMoveInfo->speed };
		const glm::vec2 newPos{ oldPos.x + (direction.x * (timeStep / 1000.f) * speed.x), oldPos.y + (direction.y * (timeStep / 1000.f) * speed.y) };
		m_pOwner->SetPosition(newPos.x, newPos.y);
	}
}


void Shining::PhysicsComponent::BlockMovement() noexcept
{
	const glm::vec2& oldPos{ m_pOwner->GetPosition() };
	m_pOwner->SetPosition(oldPos.x, oldPos.y);
}

void Shining::PhysicsComponent::SwapBuffer() noexcept
{
	//swap the pointers, can/should this be done atomically?
	
	if (m_NeedsSwap)
	{
		MoveInfo* pTemp{ m_pCurrentMoveInfo };
		m_pCurrentMoveInfo = m_pNextMoveInfo;
		m_pNextMoveInfo = pTemp;

		m_NeedsSwap = false;
	}	
}

void Shining::PhysicsComponent::SetSpeed(const float speedX, const float speedY) noexcept
{
	m_pNextMoveInfo->speed.x = speedX;
	m_pNextMoveInfo->speed.y = speedY;
	m_NeedsSwap = true;	
}

void Shining::PhysicsComponent::SetDirection(const float dirX, const float dirY) noexcept
{
	m_pNextMoveInfo->direction.x = dirX;
	m_pNextMoveInfo->direction.y = dirY;
	m_NeedsSwap = true;
}

void Shining::PhysicsComponent::SetSpeedX(const float speedX) noexcept
{
	m_pNextMoveInfo->speed.x = speedX;
	m_NeedsSwap = true;
}

void Shining::PhysicsComponent::SetSpeedY(const float speedY) noexcept
{
	m_pNextMoveInfo->speed.y = speedY;
	m_NeedsSwap = true;
}

void Shining::PhysicsComponent::SetDirectionX(const float dirX) noexcept
{
	m_pNextMoveInfo->direction.x = dirX;
	m_NeedsSwap = true;
}

void Shining::PhysicsComponent::SetDirectionY(const float dirY) noexcept
{
	m_pNextMoveInfo->direction.y = dirY;
	m_NeedsSwap = true;
}

void Shining::PhysicsComponent::SetIsMoving(const bool isMoving) noexcept
{
	m_IsMoving = isMoving;
}

const glm::vec2& Shining::PhysicsComponent::GetSpeed() const noexcept
{
	return m_pCurrentMoveInfo->speed;
}

const glm::vec2& Shining::PhysicsComponent::GetDirection() const noexcept
{
	return m_pCurrentMoveInfo->direction;
}