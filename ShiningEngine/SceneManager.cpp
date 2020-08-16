#include "ShiningEnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"
//#include "SimpleException.h"

void Shining::SceneManager::Update(const float timeStep)
{
	/*for(Scene* pScene : m_pScenes)
	{
		pScene->Update(timeStep);
	}*/

	m_pCurrentScene->Update(timeStep);
}

void Shining::SceneManager::Render()
{
	/*for (Scene* pScene : m_pScenes)
	{
		pScene->Render();
	}*/
	m_pCurrentScene->Render();
}

void Shining::SceneManager::SetScene(Scene* pScene)
{
	if (pScene == nullptr)
	{
		return;
	}

	m_pCurrentScene = pScene;
}

void Shining::SceneManager::SetScene(const int sceneIdx)
{
	m_pCurrentScene = m_pScenes.at(sceneIdx);
}

Shining::Scene* Shining::SceneManager::CreateScene(const std::string& name)
{
	const int newID{ int(m_pScenes.size()) };
	Shining::Scene* pScene = new Shining::Scene(name, newID);
	m_pScenes.push_back(pScene);
	return pScene;
}

void Shining::SceneManager::Destroy()
{
	for (Scene* pScene : m_pScenes)
	{
		delete pScene;
	}
}
