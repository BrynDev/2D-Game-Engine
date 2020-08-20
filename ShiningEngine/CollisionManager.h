#pragma once
#include "Singleton.h"
#include <map>
#include <vector>

namespace Shining
{
	class CollisionComponent;
	class TileComponent;

	class CollisionManager final : public Singleton<CollisionManager>
	{
	public:
		void RegisterCollisionComponent(CollisionComponent* const pComponent, const int tag) noexcept;
		void RemoveCollisionComponent(CollisionComponent* const pComponent, const int tag) noexcept;
		void RegisterWorldTileComponent(TileComponent* pTileComponent) noexcept;
		void AddWorldTile(const SDL_Rect& worldPosRect, const int row, const int col) noexcept;
		void ClearWorldCollision() noexcept;
		void ClearObjectCollision() noexcept;

		CollisionComponent* const GetCollidingObject(const SDL_Rect& boundingBox, const int tagToCollideWith) const noexcept;
		bool HandleWorldCollision(const SDL_Rect& boundingBox, bool canBreakTiles) noexcept; //returns true if collision happened, also potentionally modifies TileRep
	private:
		friend class Singleton<CollisionManager>;
		CollisionManager() = default;
		const bool AABBCollisionTest(const SDL_Rect& boxA, const SDL_Rect& boxB) const noexcept; //returns true if boxes are colliding

		std::multimap<int, CollisionComponent*> m_pCollidersByTag{};
		TileComponent* m_pCurrentWorldTileComponent{nullptr};

		struct TileRep //representative of a tile in the TileComponent
		{
			const SDL_Rect tileRect;
			const int row;
			const int col;
			bool hasCollision{true};
		};
		std::vector<TileRep> m_WorldCollisionTiles{};
	};
};


