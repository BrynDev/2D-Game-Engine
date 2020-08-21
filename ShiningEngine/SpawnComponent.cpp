#include "ShiningEnginePCH.h"
#include "SpawnComponent.h"

Shining::SpawnComponent::SpawnComponent(Shining::GameObject* const pObjectToSpawn, const bool doesObjectMove, const unsigned int spawnDelayMs)
	:Component()
	, m_pObjectToSpawn{ pObjectToSpawn }
	, m_SpawnDelayMs{spawnDelayMs}
	, m_SpawnTimer{0}
	, m_DoesMove{doesObjectMove}
	, m_CanStartMoving{false}
	, m_WillSpawn{false}
{
	m_pObjectToSpawn->SetActive(false);
}

Shining::SpawnComponent::SpawnComponent(Shining::GameObject* const pObjectToSpawn, const bool doesObjectMove)
	:SpawnComponent(pObjectToSpawn, doesObjectMove, 0)	
{
}

void Shining::SpawnComponent::Update(const float timeStep)
{

	if (m_CanStartMoving)
	{
		Shining::PhysicsComponent* const pPhysics{ m_pObjectToSpawn->GetComponent<Shining::PhysicsComponent>() };
		pPhysics->SetIsMoving(true);

		m_CanStartMoving = false;

	}

	if (!m_WillSpawn)
	{
		return; //Spawnobject() hasn't been called yet
	}

	if (m_SpawnDelayMs <= 0)
	{
		//no delay, spawn the object now
		ActivateObject();
		return;
	}

	m_SpawnTimer += int(timeStep);
	if(m_SpawnTimer >= m_SpawnDelayMs)
	{
		//spawn the object after the delay ends
		ActivateObject();
	}
}

void Shining::SpawnComponent::Render(const glm::vec2& /*pos*/)
{
	//empty
}

void Shining::SpawnComponent::SwapBuffer() noexcept
{
	//empty
}

void Shining::SpawnComponent::ActivateObject() noexcept
{

	if (m_DoesMove)
	{
		m_CanStartMoving = true; //delay setting physics->IsMoving to true by a frame, to make sure that the position is set properly first
	}

	m_pObjectToSpawn->SetActive(true); //instant
	m_WillSpawn = false;
	m_SpawnTimer = 0;
}

void Shining::SpawnComponent::SpawnObject(const float posX, const float posY) noexcept
{
	m_pObjectToSpawn->SetPosition(posX, posY);
	m_WillSpawn = true; //object will activate next time this component updates
}

void Shining::SpawnComponent::SpawnObject(const float posX, const float posY, const glm::vec2& speed, const glm::vec2& dir) noexcept
{
	m_pObjectToSpawn->SetPosition(posX, posY);
	Shining::PhysicsComponent* const pPhysics{ m_pObjectToSpawn->GetComponent<Shining::PhysicsComponent>() };
	if (pPhysics != nullptr)
	{
		pPhysics->SetSpeed(speed.x, speed.y);
		pPhysics->SetDirection(dir.x, dir.y);
	}

	m_WillSpawn = true; //object will activate next time this component updates
}