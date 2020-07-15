#include "ShiningEnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Shining::SceneManager::Update(const float timeStep)
{
	for(Scene* pScene : m_pScenes)
	{
		pScene->Update(timeStep);
	}
}

void Shining::SceneManager::Render()
{
	for (Scene* pScene : m_pScenes)
	{
		pScene->Render();
	}
}

Shining::Scene& Shining::SceneManager::CreateScene(const std::string& name)
{
	Scene* pScene = new Scene(name);
	m_pScenes.push_back(pScene);
	return *pScene;
}

void Shining::SceneManager::Destroy()
{
	for (Scene* pScene : m_pScenes)
	{
		delete pScene;
	}
}
