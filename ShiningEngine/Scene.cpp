#include "ShiningEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"
#include "World.h"
#include "SimpleException.h"

using namespace Shining;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) 
	: m_Name(name) 
	, m_pWorld{nullptr}
{
}

Scene::~Scene()
{
	delete m_pWorld;
	for (GameObject* pObject : m_pGameObjects)
	{
		delete pObject;
	}
}

void Scene::Add(GameObject* pObject)
{
	m_pGameObjects.push_back(pObject);
}

void Scene::Update(const float timeStep)
{
	m_pWorld->Update(timeStep);
	for(GameObject* pObject : m_pGameObjects)
	{
		pObject->Update(timeStep);
	}
}

void Scene::Render() const noexcept
{
	m_pWorld->Render();

	for (GameObject* pObject : m_pGameObjects)
	{
		pObject->Render();
	}
}

void Scene::InitWorld(const std::string& textureFile, const std::string& tilePlacementsCSV, const int tileWidth, const int tileHeight, const int nrColsTexture, const int nrRowsTexture, const int nrColsWorld, const int nrRowsWorld)
{
	try
	{
		if (m_pWorld != nullptr)
		{
			throw SimpleException{ "Exception occured: attempt to intialize the world for scene " + m_Name + " when it already has a world" };
		}
	}
	catch (const SimpleException & exception)
	{
		std::cout << exception.GetMessage() << std::endl;
	}

	m_pWorld = new World(textureFile, tilePlacementsCSV, tileWidth, tileHeight, nrColsTexture, nrRowsTexture, nrColsWorld, nrRowsWorld);
}
