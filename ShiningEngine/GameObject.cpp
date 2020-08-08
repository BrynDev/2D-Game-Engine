#include "ShiningEnginePCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

Shining::GameObject::GameObject(const float xPos, const float yPos)
	:m_Pos{xPos, yPos}
{
}

Shining::GameObject::~GameObject()
{
	for (Component* pComponent : m_pComponents)
	{
		delete pComponent;
	}
	const size_t nrObservers{ m_pObservers.size() };
	for (size_t i{ 0 }; i < nrObservers; ++i)
	{
		if (m_pObservers[i]->DecreaseSubjectCount())
		{
			delete m_pObservers[i];
		}
	}
}

void Shining::GameObject::Update(const float timeStep)
{
	for (Component* pComponent : m_pComponents)
	{
		pComponent->Update(timeStep);
	}
}

void Shining::GameObject::SetPosition(float x, float y) noexcept
{
	m_Pos.x = x;
	m_Pos.y = y;
}

const glm::vec2& Shining::GameObject::GetPosition() const noexcept
{
	return m_Pos;
}

void Shining::GameObject::Render() const
{
	for (/*const*/ Component* pComponent : m_pComponents)
	{
		pComponent->Render(m_Pos);
	}
}

void Shining::GameObject::NotifyObservers(const int eventID, void* pData) noexcept
{
	for (Shining::Observer* pObserver : m_pObservers)
	{
		pObserver->Notify(this, eventID, pData);
	}
}

void Shining::GameObject::AddComponent(Component* pComponent) noexcept
{
	m_pComponents.push_back(pComponent);
}

void Shining::GameObject::AddObserver(Observer* pObserver) noexcept
{
	m_pObservers.push_back(pObserver);
	pObserver->IncreaseSubjectCount();
}



