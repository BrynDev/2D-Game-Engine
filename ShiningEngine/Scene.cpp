#include "ShiningEnginePCH.h"
#include "Scene.h"
#include "GameObject.h"

using namespace Shining;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (GameObject* pObject : m_pGameObjects)
	{
		delete pObject;
	}
}

void Scene::Add(GameObject* pObject)
{
	m_pGameObjects.push_back(pObject);
}

void Scene::Update()
{
	for(GameObject* pObject : m_pGameObjects)
	{
		pObject->Update();
	}
}

void Scene::Render() const
{
	for (GameObject* pObject : m_pGameObjects)
	{
		pObject->Render();
	}
}

