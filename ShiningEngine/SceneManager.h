#pragma once
#include "Singleton.h"
#include <string>
#include <vector>

namespace Shining
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		void Update(const float timeStep);
		void Render();

		Scene* CreateScene(const std::string& name);	
		void SetScene(Scene* pScene);
		void SetScene(const int sceneIdx);

		void Destroy();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_pScenes;
		Scene* m_pCurrentScene{nullptr};
	};
}
