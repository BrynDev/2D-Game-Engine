#pragma once
#include "SceneManager.h"

namespace Shining
{
	//class SceneObject;
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		//void Add(SceneObject* pObject);
		void Add(GameObject* pObject);
		void Update(const float timeStep);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		//std::vector<SceneObject*> m_pObjects;
		std::vector<Shining::GameObject*> m_pGameObjects;
		static unsigned int m_IdCounter; 
	};

}
