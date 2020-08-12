#pragma once
#include "Component.h"
#include <vector>
#include <unordered_map> //TEST

namespace Shining
{
	class RenderComponent;
	
	class TileComponent final : public Shining::Component
	{
	public:
		TileComponent(const int tileWidth, const int tileHeight, const int nrColsTexture, const int nrRowsTexture, const int nrColsWorld, const int nrRowsWorld, const RenderComponent* pWeakRenderComponent);
		virtual ~TileComponent();
		

		void LoadTiles(const std::string& tilePlacementsCSV);
		virtual void Render(const glm::vec2& pos) /*const*/ override;
		virtual void Update(const float timeStep) override;
		virtual void SwapBuffer() noexcept override;
	
		TileComponent(const TileComponent& other) = delete;
		TileComponent& operator=(const TileComponent& rhs) = delete;
		TileComponent(TileComponent&& other) = delete;
		TileComponent& operator=(TileComponent&& rhs) = delete;
	private:	
		struct SharedTileInfo
		{
			SharedTileInfo(const glm::vec2& textureCoord, const bool hasCollision)
				:texCoord{textureCoord}
				, hasCollision{hasCollision}
			{
			}
			const glm::vec2 texCoord;
			const bool hasCollision;
		};
		struct Tile
		{
			const SharedTileInfo* pSharedInfo;
			 //glm::vec2 worldPos;
		};

		std::vector<std::vector<Tile>> m_pTiles; //2D grid of tiles
		//std::unordered_map<int, SharedTileInfo> m_TileInfoByID;
		std::unordered_map<int, const SharedTileInfo* const> m_TileInfoByID;
		const Shining::RenderComponent* m_pWeakRenderComponent;
		const int m_TileWidth;
		const int m_TileHeight;
		const int m_NrColsTexture;
		const int m_NrRowsTexture;
		const int m_NrColsWorld;
		const int m_NrRowsWorld;
	};
}


