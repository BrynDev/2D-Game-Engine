#include "ShiningEnginePCH.h"
#include "Scene.h"
#include "World.h"
#include "SimpleException.h"
#include "CollisionManager.h"
#include "InputContext.h"
#include "InputManager.h"


Shining::InputContext Shining::Scene::m_NullInput{};

Shining::Scene::Scene(const std::string& name, const int ID)
	: m_Name(name)
	, m_MusicFileName{}
	, m_pWorld{ nullptr }
	, m_ID{ ID }
	, m_pInputContext{&m_NullInput}
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

	if (m_pInputContext != &m_NullInput)
	{
		if (m_pInputContext->DecreaseReferenceCount())
		{
			delete m_pInputContext;
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

	for (Shining::GameObject* const pObject : m_pGameObjects)
	{
		pObject->Render();
	}
}

void Shining::Scene::Add(Shining::GameObject* pObject)
{
	m_pGameObjects.push_back(pObject);
	pObject->IncreaseReferenceCount();
}

const int Shining::Scene::GetID() const noexcept
{
	return m_ID;
}

void Shining::Scene::InitWorld(const std::string& textureFile, const std::string& tilePlacementsCSV, const int worldScale, const int tileWidth, const int tileHeight, const int nrColsTexture, const int nrRowsTexture, const int nrColsWorld, const int nrRowsWorld)
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
		std::cout << exception.GetExceptionMessage() << std::endl;
	}

	m_pWorld = new World(textureFile, tilePlacementsCSV, worldScale, tileWidth, tileHeight, nrColsTexture, nrRowsTexture, nrColsWorld, nrRowsWorld);
}

void Shining::Scene::InitInputContext(InputContext* pInputContext) noexcept
{
	if (pInputContext != nullptr)
	{
		m_pInputContext = pInputContext;
		pInputContext->IncreaseReferenceCount();
	}
}

void Shining::Scene::InitMusic(const std::string& fileName) noexcept
{
	m_MusicFileName = fileName;
}

void Shining::Scene::ResetObjectsPos() noexcept
{
	for (Shining::GameObject* pObject : m_pGameObjects)
	{
		pObject->ResetPos();
	}
}

void Shining::Scene::SetObjectCollision() const noexcept
{
	Shining::CollisionManager& instance{ Shining::CollisionManager::GetInstance() };
	Shining::CollisionManager::GetInstance().ClearObjectCollision(); //clear old scene colliders

	for (Shining::GameObject* pObject : m_pGameObjects)
	{
		Shining::CollisionComponent* pCollision{ pObject->GetComponent<Shining::CollisionComponent>() };
		if (pCollision != nullptr) //check if this component has collision
		{
			instance.RegisterCollisionComponent(pCollision, pCollision->GetTag()); //set this scene's colliders
		}
	}
}

void Shining::Scene::SetWorldCollision() noexcept
{
	if (m_pWorld != nullptr)
	{
		Shining::CollisionManager::GetInstance().ClearWorldCollision(); //clear old scene world
		m_pWorld->SetCollision(); //set this scene's world
	}
}

void Shining::Scene::SetInputContext() const noexcept
{
	Shining::InputManager::GetInstance().SetInputContext(m_pInputContext);
}

void Shining::Scene::PlayMusic() const noexcept
{
	Shining::AudioPlayer& audio{ Shining::AudioPlayer::GetInstance() };
	audio.StopMusic();
	if (!m_MusicFileName.empty())
	{
		audio.PlayMusicLooped(m_MusicFileName);
	}	
}