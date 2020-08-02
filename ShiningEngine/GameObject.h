#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)

#include <vector>
#include <typeinfo>

namespace Shining
{
	class Texture2D;
	class Component;
	class GameObject final
	{
	public:
		GameObject(const float xPos, const float yPos);
		virtual ~GameObject();

		virtual void Update(const float timeStep);
		virtual void Render() const;
		void SetPosition(float x, float y) noexcept;
		glm::vec2 GetPosition() const noexcept;
		void AddComponent(Component* pComponent) noexcept;

		template<typename T>
		T* GetComponent() const;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		glm::vec2 m_Pos;
		//Transform m_Transform;
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
