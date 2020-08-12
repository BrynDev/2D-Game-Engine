#include "ShiningEnginePCH.h"
#include "TileComponent.h"
#include "CSVParser.h"
#include "SimpleException.h"

Shining::TileComponent::TileComponent(const int tileWidth, const int tileHeight, const int nrColsTexture, const int nrRowsTexture, const int nrColsWorld, const int nrRowsWorld, const RenderComponent* pWeakRenderComponent)
	:Component()
	, m_TileWidth{tileWidth}
	, m_TileHeight{tileHeight}
	, m_NrColsTexture{nrColsTexture}
	, m_NrRowsTexture{nrRowsTexture}
	, m_NrColsWorld{nrColsWorld}
	, m_NrRowsWorld{nrRowsWorld}
	, m_pWeakRenderComponent{pWeakRenderComponent}
{
	//resize the 2D vector that represents the tiles
	m_pTiles.resize(nrRowsWorld);
	for (int row{ 0 }; row < nrRowsWorld; ++row)
	{
		m_pTiles[row].resize(nrColsWorld);
	}

	//the first tile in the tileset is considered empty and has no collision, all other tiles do
	SharedTileInfo* pEmptyTileInfo{ new SharedTileInfo(glm::vec2{0,0},false) };
	m_TileInfoByID.insert(std::make_pair(0, pEmptyTileInfo));
}

void Shining::TileComponent::Render(const glm::vec2& pos) /*const*/
{
	SDL_Rect destRect{int(pos.x), int(pos.y), m_TileWidth, m_TileHeight};
	for (int row{ 0 }; row < m_NrRowsWorld; ++row)
	{
		for (int col{ 0 }; col < m_NrColsWorld; ++col)
		{
			glm::vec2 texCoord{ m_pTiles[row][col].pSharedInfo->texCoord };

			SDL_Rect srcRect{ int(texCoord.x), int(texCoord.y), m_TileWidth, m_TileHeight };
			m_pWeakRenderComponent->RenderTile(srcRect, destRect);

			destRect.x += m_TileWidth;
		}
		destRect.x = int(pos.x);
		destRect.y += m_TileHeight;
	}
}

void Shining::TileComponent::Update(const float /*timeStep*/)
{
	//TODO
}

void Shining::TileComponent::SwapBuffer() noexcept
{
	//currently not needed, probably later
}

void Shining::TileComponent::LoadTiles(const std::string& tilePlacementsCSV)
{
	//parse the CSV file
	const CSVParser parser{};
	std::vector<int> tileIDs{};
	try
	{
		parser.LoadTileMapData(tilePlacementsCSV, tileIDs);
	}
	catch (const SimpleException& exception)
	{
		std::cout << exception.GetMessage() << std::endl;

		//fill the tile array with default values
		int idx{ 0 };
		for (int row{ 0 }; row < m_NrRowsWorld; ++row)
		{
			for (int col{ 0 }; col < m_NrColsWorld; ++col)
			{
		
				//Tile defaultTile{ m_TileInfoByID[0] };
				m_pTiles[row][col] = Tile{m_TileInfoByID[0]};
				++idx;
			}
		}
		return; //exit this function
	}

	//fill in the tile data for each tile according to the parsed file
	int idx{ 0 };
	for (int row{ 0 }; row < m_NrRowsWorld; ++row)
	{
		for (int col{ 0 }; col < m_NrColsWorld; ++col)
		{
			const int currentTileID{ tileIDs[idx] };

			//check if this ID has already been loaded
			auto foundIt{ m_TileInfoByID.find(currentTileID) };
			if (foundIt != m_TileInfoByID.end())
			{
				//this type of tile is already in the map
				m_pTiles[row][col] = Tile{ foundIt->second };
			}
			else
			{
				//this is a new type of tile
				//calculate texPos
				const int texXPos{ (currentTileID % m_NrColsTexture) * m_TileWidth };
				const int texYPos{ (currentTileID / m_NrColsTexture) * m_TileHeight };
				//add the TileInfo to the map
				SharedTileInfo* pInfo{ new SharedTileInfo(glm::vec2(texXPos, texYPos), true) };
				m_TileInfoByID.insert(std::make_pair(currentTileID, pInfo));
				m_pTiles[row][col] = Tile{ pInfo };
			}
			++idx;
		}
	}
}

Shining::TileComponent::~TileComponent()
{
	for (auto pair : m_TileInfoByID)
	{
		delete pair.second;
	}
}