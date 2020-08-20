#pragma once
#include "SceneManager.h"

namespace Shining
{
	class GameObject;
	class World;
	class InputContext;

	class Scene
	{
		friend Scene* SceneManager::CreateScene(const std::string& name);
	public:
		void Update(const float timeStep);
		void Render() const noexcept;

		void Add(GameObject* pObject);
		void InitWorld(const std::string& textureFile, const std::string& tilePlacementsCSV, const int worldScale, const int tileWidth, const int tileHeight, const int nrColsTexture, const int nrRowsTexture, const int nrColsWorld, const int nrRowsWorld);
		void InitInputContext(InputContext* pInputContext) noexcept;

		void SetWorldCollision() noexcept;
		void SetObjectCollision() const noexcept;
		void SetInputContext() const noexcept;
		const int GetID() const noexcept;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		explicit Scene(const std::string& name, const int ID);
		static InputContext m_NullInput;
		std::vector<Shining::GameObject*> m_pGameObjects;
		std::string m_Name;
		World* m_pWorld;
		InputContext* m_pInputContext;
		const int m_ID;
	};
}
