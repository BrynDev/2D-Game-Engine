#pragma once

namespace Shining
{
	class TileComponent;
	class RenderComponent;

	class World final
	{
	public:
	
		World(const std::string& textureFile, const std::string& tilePlacementsCSV, const int tileWidth, const int tileHeight, const int nrColsTexture, const int nrRowsTexture, const int nrColsWorld, const int nrRowsWorld);
		~World();
		void Render() const noexcept;
		void Update(const float timeStep);

		World(const World& other) = delete;
		World& operator=(const World& rhs) = delete;
		World(World&& other) = delete;
		World& operator=(World&& rhs) = delete;
	private:
		Shining::TileComponent* m_pTileComponent;
		Shining::RenderComponent* m_pRenderComponent;
	};
}