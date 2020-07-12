#include "ShiningEnginePCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Component.h"

Shining::GameObject::~GameObject()
{
	for (Component* pComponent : m_pComponents)
	{
		delete pComponent;
	}
}

void Shining::GameObject::Update()
{
	for (Component* pComponent : m_pComponents)
	{
		pComponent->Update();
	}
}

void Shining::GameObject::Render() const
{
	for (/*const*/ Component* pComponent : m_pComponents)
	{
		pComponent->Render(m_Transform.GetPosition());
	}
}

void Shining::GameObject::AddComponent(Component* pComponent) noexcept
{
	m_pComponents.push_back(pComponent);
}

void Shining::GameObject::SetPosition(float x, float y) noexcept
{
	m_Transform.SetPosition(x, y, 0.0f);
}

