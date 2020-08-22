#pragma once
#include "Component.h"
#include "NullCollision.h"

namespace Shining 
{
	class RenderComponent;
	class CollisionBehavior;
	class GameObject;

	class CollisionComponent final : public Component
	{
	public:
		CollisionComponent(GameObject* const pOwner, const RenderComponent* const pComponent, const int tag, const bool hasWorldCollision, const bool canBreakTiles); //collider will match the sprite
		CollisionComponent(GameObject* const pOwner, const int width, const int height, const int tag, const bool hasWorldCollision, const bool canBreakTiles); //define custom collider size
		virtual ~CollisionComponent();

		virtual void Update(const float timeStep) override;
		virtual void Render(const glm::vec2& pos) const override;
		virtual void SwapBuffer() noexcept override;

		const SDL_Rect GetBoundingBox() const noexcept;
		void ResolveCollision(const int collidedTag) noexcept;
		void ResolveWorldCollision() noexcept;
		void AddTargetTag(const int tag) noexcept;
		void RemoveTargetTag(const int tag) noexcept;
		void SetBehavior(CollisionBehavior* const pBehavior) noexcept;
		const int GetTag() const noexcept;

		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(const CollisionComponent& rhs) = delete;
		CollisionComponent(CollisionComponent&& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& rhs) = delete;
	private:
		GameObject* const m_pOwner;
		std::set<int> m_TagsToCollideWith;
		CollisionBehavior* m_pCollisionBehavior;
		static NullCollision m_NullBehavior;
		const int m_BoxWidth;
		const int m_BoxHeight;
		const int m_Tag;
		bool m_CanCollideWithWorld;
		const bool m_CanBreakTiles;
	};
}


