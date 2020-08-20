#include "ShiningEnginePCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

Shining::GameObject::GameObject(const float xPos, const float yPos)
	:m_CurrentPos{xPos, yPos}
	, m_NextPos{xPos,yPos}
	, m_pComponents{}
	, m_pObservers{}
	, m_ReferenceCount{0}
	, m_IsActive{true}
	, m_NeedsSwap{false}
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
	if (m_IsActive)
	{
		for (Component* pComponent : m_pComponents)
		{
			pComponent->Update(timeStep);
		}
	}	
}

void Shining::GameObject::Render() const
{
	if (m_IsActive)
	{
		for (/*const*/ Component* pComponent : m_pComponents)
		{
			pComponent->Render(m_CurrentPos);
		}
	}

}

void Shining::GameObject::SwapBuffer() noexcept
{
	if (m_NeedsSwap)
	{
		m_CurrentPos = m_NextPos;
		m_NeedsSwap = false;
	}
	for (Component* pComponent : m_pComponents)
	{
		pComponent->SwapBuffer();
	}
}

void Shining::GameObject::SetPosition(float x, float y) noexcept
{
	m_NextPos.x = x;
	m_NextPos.y = y;
	m_NeedsSwap = true;
}

const glm::vec2& Shining::GameObject::GetPosition() const noexcept
{
	return m_CurrentPos;
}

const glm::vec2& Shining::GameObject::GetNextPosition() const noexcept
{
	return m_NextPos;
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

void Shining::GameObject::SetActive(const bool isActive) noexcept
{
	m_IsActive = isActive;
}

void Shining::GameObject::IncreaseReferenceCount() noexcept
{
	++m_ReferenceCount;
}

bool Shining::GameObject::DecreaseReferenceCount() noexcept
{
	--m_ReferenceCount;
	return(m_ReferenceCount <= 0);
}


