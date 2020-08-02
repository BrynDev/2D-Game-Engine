#include "ShiningEnginePCH.h"
#include "PhysicsComponent.h"


Shining::PhysicsComponent::PhysicsComponent(GameObject* const pOwner)
	:m_pOwner{pOwner}
	, m_Speed{0,0}
	, m_Direction{0,0}
{
}

void Shining::PhysicsComponent::Render(const glm::vec2& /*pos*/) /*const*/ noexcept
{
	//UNUSED FUNCTION
}

void Shining::PhysicsComponent::Update(const float /*timeStep*/) noexcept
{
	//todo?
}

void Shining::PhysicsComponent::MoveOwner(const float timeStep) noexcept
{
	const glm::vec2 oldPos{ m_pOwner->GetPosition() };
	const glm::vec2 newPos{ oldPos.x + (m_Direction.x * (timeStep / 1000.f) * m_Speed.x), oldPos.y + (m_Direction.y * (timeStep / 1000.f) * m_Speed.y) };
	m_pOwner->SetPosition(newPos.x, newPos.y);
}

void Shining::PhysicsComponent::SetSpeed(const float speedX, const float speedY) noexcept
{
	m_Speed.x = speedX;
	m_Speed.y = speedY;
}

void Shining::PhysicsComponent::SetDirection(const float dirX, const float dirY) noexcept
{
	m_Direction.x = dirX;
	m_Direction.y = dirY;
}

void Shining::PhysicsComponent::SetSpeedX(const float speedX) noexcept
{
	m_Speed.x = speedX;
}

void Shining::PhysicsComponent::SetSpeedY(const float speedY) noexcept
{
	m_Speed.y = speedY;
}

void Shining::PhysicsComponent::SetDirectionX(const float dirX) noexcept
{
	m_Direction.x = dirX;
}

void Shining::PhysicsComponent::SetDirectionY(const float dirY) noexcept
{
	m_Direction.y = dirY;
}

const glm::vec2& Shining::PhysicsComponent::GetSpeed() const noexcept
{
	return m_Speed;
}

const glm::vec2& Shining::PhysicsComponent::GetDirection() const noexcept
{
	return m_Direction;
}

const bool Shining::PhysicsComponent::IsNotMoving() const noexcept
{
	//
	return((m_Speed.x < FLT_EPSILON && m_Speed.x > -FLT_EPSILON) && (m_Speed.y < FLT_EPSILON && m_Speed.y > -FLT_EPSILON));
}