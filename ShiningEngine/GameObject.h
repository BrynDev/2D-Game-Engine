#pragma once
#include "Transform.h"
#include <vector>

namespace Shining
{
	class Texture2D;
	class Component;
	class GameObject final
	{
	public:
		virtual void Update(const float timeStep);
		virtual void Render() const;

		void SetPosition(float x, float y) noexcept;
		void AddComponent(Component* pComponent) noexcept;

		template<typename T>
		T* GetComponent() const;

		GameObject() = default;
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_Transform;
		std::vector<Shining::Component*> m_pComponents;
	};
}

template<typename T>
T* Shining::GameObject::GetComponent() const
{
	for (Component* pComponent : m_pComponents)
	{
		if (typeid(T) == typeid(*pComponent))
		{
			return static_cast<T*>(pComponent);
		}
	}
	//maybe an exception should go here
	return nullptr;
}
