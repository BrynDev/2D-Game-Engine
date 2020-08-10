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
}

//consider using a fixed size allocator for tiles -> improves locality

void Shining::TileComponent::Render(const glm::vec2& pos) /*const*/
{
	SDL_Rect destRect{int(pos.x), int(pos.y), m_TileWidth, m_TileHeight};
	for (int row{ 0 }; row < m_NrRowsWorld; ++row)
	{
		for (int col{ 0 }; col < m_NrColsWorld; ++col)
		{
			int currentTileId{ m_pTiles[row][col].id };
			
			//calculate source rect offsets
			const int yOffset{ currentTileId / m_NrColsTexture };
			const int xOffset{ currentTileId % m_NrColsTexture };

			SDL_Rect srcRect{ xOffset * m_TileWidth, yOffset * m_TileHeight, m_TileWidth, m_TileHeight };
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

/*const Shining::Tile& Shining::TileComponent::GetTile(const int indexX, const int indexY) const noexcept
{
	return m_pTiles[indexX][indexY];
}*/

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
		for (int row{ 0 }; row < m_NrRowsWorld; ++row)
		{
			for (int col{ 0 }; col < m_NrColsWorld; ++col)
			{

				m_pTiles[row][col] = Tile{0}; 
				
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
			
			m_pTiles[row][col] = Tile{ tileIDs[idx] };
			++idx;
		}
	}
}

Shining::TileComponent::~TileComponent()
{
	/*const size_t nrRows{ m_pTiles.size() };
	const size_t nrCols{ m_pTiles[0].size() };
	for (unsigned int i{ 0 }; i < nrRows; ++i)
	{
		for (unsigned int j{ 0 }; j < nrCols; ++j)
		{
			delete m_pTiles[i][j];
		}
	}*/
}