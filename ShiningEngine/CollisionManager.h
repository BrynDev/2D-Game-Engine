#pragma once
#include "Singleton.h"
#include <set>
#include <map>

namespace Shining
{
	class CollisionComponent;

	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void RegisterCollisionComponent(CollisionComponent* const pComponent, const int tag) noexcept;
		void RemoveCollisionComponent(CollisionComponent* const pComponent, const int tag) noexcept;
		void Destroy();
		//bool IsColliding(const SDL_Rect& boundingBox, const int currentTag, const int tagToCollideWith, const bool isStatic) const noexcept;
		CollisionComponent* const GetCollidingObject(const SDL_Rect& boundingBox, const int tagToCollideWith) const noexcept;
	private:
		friend class Singleton<CollisionManager>;
		CollisionManager() = default;
		std::multimap<int, CollisionComponent*> m_pCollidersByTag;
	};
};


