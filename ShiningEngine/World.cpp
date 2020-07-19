#include "ShiningEnginePCH.h"
#include "World.h"
#include "TileComponent.h"

Shining::World::World(const TileMapDescriptor& /*tileMap*/, const std::string& /*tilePlacementsCSV*/, const int /*nrTilesX*/, const int /*nrTilesY*/)
	//:m_pTiles{ new TileComponent() }
{
}

Shining::World::~World()
{
	//delete m_pTiles;
}

void Shining::World::Render() const
{
	//m_pTiles->Render(glm::vec3{0,0,0}); //dont need to pass a position here, component takes care of it
}