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
		void Render() const;
		void SwapBuffer() noexcept;

		Scene* CreateScene(const std::string& name);
		void AdvanceScene();
		void SetScene(Scene* pScene);
		void SetScene(const int sceneIdx);

		void Destroy();
	private:
		friend class Singleton<SceneManager>;
		SceneManager();
		std::vector<Scene*> m_pScenes;
		Scene* m_pCurrentScene;
		Scene* m_pNextScene;
		bool m_NeedsSwap;
	};
}
