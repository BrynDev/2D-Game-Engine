#pragma once
#include "Component.h"
#include <vector>

namespace Shining
{
	class RenderComponent;

	struct Tile
	{
		int id;
	};

	class TileComponent final : public Shining::Component
	{
	public:
		TileComponent(const int tileWidth, const int tileHeight, const int nrColsTexture, const int nrRowsTexture, const int nrColsWorld, const int nrRowsWorld, const RenderComponent* pWeakRenderComponent);
		virtual ~TileComponent();
		TileComponent(const TileComponent& other) = delete;
		TileComponent& operator=(const TileComponent& rhs) = delete;
		TileComponent(TileComponent&& other) = delete;
		TileComponent& operator=(TileComponent&& rhs) = delete;

		void LoadTiles(const std::string& tilePlacementsCSV);
		virtual void Render(const glm::vec2& pos) /*const*/ override;
		virtual void Update(const float timeStep) override;
		//const Tile& GetTile(const int indexX, const int indexY) const noexcept;
		
	private:
		std::vector<std::vector<Tile>> m_pTiles; //2D grid of tiles
		const Shining::RenderComponent* m_pWeakRenderComponent;
		const int m_TileWidth;
		const int m_TileHeight;
		const int m_NrColsTexture;
		const int m_NrRowsTexture;
		const int m_NrColsWorld;
		const int m_NrRowsWorld;
	};
}


