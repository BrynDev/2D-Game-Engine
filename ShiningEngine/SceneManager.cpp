#include "ShiningEnginePCH.h"
#include "SceneManager.h"
#include "Scene.h"

void Shining::SceneManager::Update(const float timeStep)
{
	m_pCurrentScene->Update(timeStep);
}

void Shining::SceneManager::Render()
{
	m_pCurrentScene->Render();
}

void Shining::SceneManager::SwapBuffer() noexcept
{
	if (!m_NeedsSwap)
	{
		return;
	}

	m_pCurrentScene = m_pNextScene;
	m_pNextScene = nullptr;
	m_NeedsSwap = false;

	m_pCurrentScene->SetWorldCollision();
	m_pCurrentScene->SetObjectCollision();
	m_pCurrentScene->SetInputContext();
}

void Shining::SceneManager::AdvanceScene()
{
	const int currentIdx{ m_pCurrentScene->GetID() };
	const int nextIdx{ currentIdx + 1 };

	SetScene(nextIdx);
}

void Shining::SceneManager::SetScene(Scene* pScene)
{
	if (pScene == nullptr)
	{
		return;
	}

	m_pNextScene = pScene;
	m_NeedsSwap = true;
}

void Shining::SceneManager::SetScene(const int sceneIdx)
{
	if (sceneIdx >= m_pScenes.size())
	{
		return;
	}

	m_pNextScene = m_pScenes[sceneIdx];
	m_NeedsSwap = true;
}

Shining::Scene* Shining::SceneManager::CreateScene(const std::string& name)
{
	const int newID{ int(m_pScenes.size()) };
	Shining::Scene* pScene = new Shining::Scene(name, newID);
	m_pScenes.push_back(pScene);
	return pScene;
}

Shining::SceneManager::SceneManager()
	:Singleton()
	, m_pScenes{}
	, m_pCurrentScene{nullptr}
	, m_pNextScene{nullptr}
	, m_NeedsSwap{false}
{
}

void Shining::SceneManager::Destroy()
{
	for (Scene* pScene : m_pScenes)
	{
		delete pScene;
	}
}
