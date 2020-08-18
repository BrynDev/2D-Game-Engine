#include "ShiningEnginePCH.h"
#include "CollisionManager.h"
#include <algorithm>
#include "TileComponent.h"

const bool Shining::CollisionManager::AABBCollisionTest(const SDL_Rect& boxA, const SDL_Rect& boxB) const noexcept
{
	return
		(
			boxA.x + boxA.w >= boxB.x && //rightA >= leftB
			boxB.x + boxB.w >= boxA.x && //rightB >= leftA
			boxA.y + boxA.h >= boxB.y && //bottomA >= topB
			boxB.y + boxB.h >= boxA.y //bottomB >= topA
			);
}

Shining::CollisionComponent* const Shining::CollisionManager::GetCollidingObject(const SDL_Rect& boundingBox, const int tagToCollideWith) const noexcept
{
	using mapIt = std::multimap<int, CollisionComponent*>::const_iterator;

	//AABB collision method
	std::pair<mapIt, mapIt> range{ m_pCollidersByTag.equal_range(tagToCollideWith) };
	if (std::distance(range.first, range.second) == 0) //check if this key exists within the multimap
	{
		//this key is not present in the multimap
		return nullptr;
	}
	for (mapIt it{ range.first }; it != range.second; ++it)
	{
		const SDL_Rect otherBox{ it->second->GetBoundingBox() };
		if (AABBCollisionTest(boundingBox, otherBox))
		{
			return it->second;
		}
	}
	return nullptr;
}

bool Shining::CollisionManager::HandleWorldCollision(const SDL_Rect& boundingBox, bool canBreakTiles) noexcept
{
	//this could be optimized to check less tiles each frame, possibly todo
	for (TileRep& tile : m_WorldCollisionTiles)
	{
		if (tile.hasCollision)
		{
			if (!AABBCollisionTest(boundingBox, tile.tileRect))
			{
				continue; //no collision with this tile
			}

			if (canBreakTiles)
			{
				tile.hasCollision = false; //break this tile, don't check collision for it anymore
				m_pCurrentWorldTileComponent->BreakTile(tile.row, tile.col);
			}
			return true;
		}	
	}

	return false; //no collision
}

void Shining::CollisionManager::RegisterCollisionComponent(CollisionComponent* const pComponent, const int tag) noexcept
{
	m_pCollidersByTag.insert(std::make_pair(tag, pComponent));
}

void  Shining::CollisionManager::RegisterWorldTileComponent(TileComponent* pTileComponent) noexcept
{
	m_pCurrentWorldTileComponent = pTileComponent;
}

void Shining::CollisionManager::AddWorldTile(const SDL_Rect& worldPosRect, const int row, const int col) noexcept
{
	const TileRep tile{ worldPosRect, row, col };
	m_WorldCollisionTiles.push_back(tile);
}

void Shining::CollisionManager::RemoveCollisionComponent(CollisionComponent* const pComponent, const int tag) noexcept
{
	using mapIt = std::multimap<int, CollisionComponent*>::iterator;
	//get all the elements with this key
	std::pair<mapIt, mapIt> range{ m_pCollidersByTag.equal_range(tag) }; 
	//get the iterator to pComponent from this range
	mapIt toErase{ std::find_if(range.first, range.second, [pComponent](std::pair<int, CollisionComponent*> pair) {
		return (pair.second == pComponent);
		}) };
	//erase the element using the iterator
	if (toErase != m_pCollidersByTag.end())
	{
		m_pCollidersByTag.erase(toErase);
	}
}

void Shining::CollisionManager::ClearWorldCollision() noexcept
{
	m_WorldCollisionTiles.clear();
}

void Shining::CollisionManager::ClearObjectCollision() noexcept
{
	m_pCollidersByTag.clear();
}