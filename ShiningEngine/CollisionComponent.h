#pragma once
#include "Component.h"

namespace Shining 
{
	class RenderComponent;

	class CollisionComponent final : public Component
	{
	public:
		CollisionComponent(const glm::vec2* pPosition, const RenderComponent* const pComponent, const int tag, const bool isStatic); //collider will match the sprite
		CollisionComponent(const glm::vec2* pPosition, const int width, const int height, const int tag, const bool isStatic); //define custom collider size
		virtual ~CollisionComponent();

		virtual void Update(const float timeStep) override;
		virtual void Render(const glm::vec2& pos) override;
		const SDL_Rect GetBoundingBox() const noexcept;
		void AddTargetTag(const int tag) noexcept;
		void RemoveTargetTag(const int tag) noexcept;
		void AddTargetTags(const std::set<int>& targets) noexcept;

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& rhs) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& rhs) = delete;
	private:
		std::set<int> m_TagsToCollideWith;
		const glm::vec2* m_pOwnerPos;
		const int m_BoxWidth;
		const int m_BoxHeight;
		const int m_Tag;
		const bool m_IsStatic;
	};
}


