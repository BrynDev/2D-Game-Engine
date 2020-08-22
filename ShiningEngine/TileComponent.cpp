#include "ShiningEnginePCH.h"
#include "TileComponent.h"
#include "CSVParser.h"
#include "SimpleException.h"
#include "CollisionManager.h"

Shining::TileComponent::TileComponent(const int tileWidth, const int tileHeight, const int nrColsTexture, const int nrRowsTexture, const int nrColsWorld, const int nrRowsWorld, const int worldScale, const RenderComponent* pRenderComponent)
	:Component()
	, m_TileWidth{tileWidth}
	, m_TileHeight{tileHeight}
	, m_NrColsTexture{nrColsTexture}
	, m_NrRowsTexture{nrRowsTexture}
	, m_NrColsWorld{nrColsWorld}
	, m_NrRowsWorld{nrRowsWorld}
	, m_WorldScale{worldScale}
	, m_pRenderComponent{pRenderComponent}
{
	//resize the 2D vector that represents the tiles
	m_Tiles.resize(nrRowsWorld);
	for (int row{ 0 }; row < nrRowsWorld; ++row)
	{
		m_Tiles[row].resize(nrColsWorld);
	}

	//the first tile in the tileset is considered empty and has no collision, all other tiles do
	SharedTileInfo* pEmptyTileInfo{ new SharedTileInfo(glm::vec2{0,0},false) };
	m_TileInfoByID.insert(std::make_pair(0, pEmptyTileInfo));
}

void Shining::TileComponent::Render(const glm::vec2& /*pos*/) const
{
	SDL_Rect destRect{0, 0, m_TileWidth * m_WorldScale, m_TileHeight * m_WorldScale };
	for (int row{ 0 }; row < m_NrRowsWorld; ++row)
	{
		for (int col{ 0 }; col < m_NrColsWorld; ++col)
		{
			glm::vec2 texCoord{ m_Tiles[row][col].pSharedInfo->texCoord };

			SDL_Rect srcRect{ int(texCoord.x), int(texCoord.y), m_TileWidth, m_TileHeight };
			m_pRenderComponent->RenderTile(srcRect, destRect);

			destRect.x += destRect.w;
		}
		destRect.x = 0;
		destRect.y += destRect.h;
	}
}

void Shining::TileComponent::Update(const float /*timeStep*/)
{
	//empty
}

void Shining::TileComponent::SwapBuffer() noexcept
{
	//not needed
}

void Shining::TileComponent::BreakTile(const int row, const int col) noexcept
{
	m_Tiles[row][col].pSharedInfo = m_TileInfoByID[0]; //ID at index 0 is the designated "empty" tile
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
		std::cout << exception.GetExceptionMessage() << std::endl;

		//fill the tile array with default values
		int idx{ 0 };
		for (int row{ 0 }; row < m_NrRowsWorld; ++row)
		{
			for (int col{ 0 }; col < m_NrColsWorld; ++col)
			{
				m_Tiles[row][col] = Tile{m_TileInfoByID[0]};
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
				m_Tiles[row][col] = Tile{ foundIt->second };
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
				m_Tiles[row][col] = Tile{ pInfo };
			}
			++idx;
		}
	}
}

void Shining::TileComponent::SetCollision() noexcept
{
	Shining::CollisionManager& instance{ Shining::CollisionManager::GetInstance() };
	SDL_Rect destRect{ 0, 0, m_TileWidth * m_WorldScale, m_TileHeight * m_WorldScale };
	for (int row{ 0 }; row < m_NrRowsWorld; ++row)
	{
		for (int col{ 0 }; col < m_NrColsWorld; ++col)
		{
			if (m_Tiles[row][col].pSharedInfo->hasCollision)
			{
				instance.AddWorldTile(destRect, row, col);
			}

			destRect.x += destRect.w;
		}
		destRect.x = 0;
		destRect.y += destRect.h;
	}

	instance.RegisterWorldTileComponent(this); //register this world so the collision component can break tiles if it needs to
}

Shining::TileComponent::~TileComponent()
{
	for (auto pair : m_TileInfoByID)
	{
		delete pair.second;
	}
}