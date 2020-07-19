#pragma once

#include <vector>

class TileComponent;

namespace Shining
{
	struct TileMapDescriptor
	{
		const std::string path{};
		const int tileWidth{};
		const int tileHeight{};
		const int nrCols{};
		const int nrRows{};
	};

	class World final
	{
	public:
		World(const TileMapDescriptor& tileMap, const std::string& tilePlacementsCSV, const int nrTilesX, const int nrTilesY );
		~World();
		void Render() const;

		World(const World& other) = delete;
		World& operator=(const World& rhs) = delete;
		World(World&& other) = delete;
		World& operator=(World&& rhs) = delete;
	private:
		TileComponent* m_pTiles;
	};
}