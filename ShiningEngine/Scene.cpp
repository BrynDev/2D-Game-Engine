#include "ShiningEnginePCH.h"
#include "Scene.h"
//#include "GameObject.h"
#include "World.h"
#include "SimpleException.h"


Shining::Scene::Scene(const std::string& name, const int ID)
	: m_Name(name)
	, m_pWorld{ nullptr }
	, m_ID{ ID }
{
}

Shining::Scene::~Scene()
{
	if (m_pWorld != nullptr)
	{
		delete m_pWorld;
	}

	for (Shining::GameObject* pObject : m_pGameObjects)
	{
		if (pObject->DecreaseReferenceCount()) //true if ref count is 0
		{
			delete pObject;
		}		
	}
}

void Shining::Scene::Update(const float timeStep)
{
	if (m_pWorld != nullptr)
	{
		m_pWorld->Update(timeStep);
	}

	for (Shining::GameObject* pObject : m_pGameObjects)
	{
		pObject->SwapBuffer();
	}

	for(Shining::GameObject* pObject : m_pGameObjects)
	{
		pObject->Update(timeStep);
	}
}

void Shining::Scene::Render() const noexcept
{
	if (m_pWorld != nullptr)
	{
		m_pWorld->Render();
	}

	for (Shining::GameObject* pObject : m_pGameObjects)
	{
		pObject->Render();
	}
}

void Shining::Scene::Add(Shining::GameObject* pObject)
{
	m_pGameObjects.push_back(pObject);
	pObject->IncreaseReferenceCount();
}


void Shining::Scene::InitWorld(const std::string& textureFile, const std::string& tilePlacementsCSV, const int tileWidth, const int tileHeight, const int nrColsTexture, const int nrRowsTexture, const int nrColsWorld, const int nrRowsWorld)
{
	try
	{
		if (m_pWorld != nullptr)
		{
			throw Shining::SimpleException{ "Exception occured: attempt to intialize the world for scene " + m_Name + " when it already has a world" };
		}
	}
	catch (const Shining::SimpleException & exception)
	{
		std::cout << exception.GetMessage() << std::endl;
	}

	m_pWorld = new World(textureFile, tilePlacementsCSV, tileWidth, tileHeight, nrColsTexture, nrRowsTexture, nrColsWorld, nrRowsWorld);
}
