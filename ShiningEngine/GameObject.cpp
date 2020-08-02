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

glm::vec2 Shining::GameObject::GetPosition() const noexcept
{
	return m_Pos;
}

void Shining::GameObject::Render() const
{
	for (/*const*/ Component* pComponent : m_pComponents)
	{
		//pComponent->Render(m_Transform.GetPosition());
		pComponent->Render(m_Pos);
	}
}



void Shining::GameObject::AddComponent(Component* pComponent) noexcept
{
	m_pComponents.push_back(pComponent);
}



