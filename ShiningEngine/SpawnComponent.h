#pragma once
#include "Component.h"

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#pragma warning(pop)


namespace Shining
{
	class SpawnComponent final : public Component
	{
	public:
		explicit SpawnComponent(GameObject* const pObjectToSpawn, const bool doesObjectMove, const unsigned int spawnDelayMs);
		explicit SpawnComponent(GameObject* const pObjectToSpawn, const bool doesObjectMove);
		virtual ~SpawnComponent() = default;

		virtual void Update(const float timeStep) override;
		virtual void Render(const glm::vec2& pos) override;
		virtual void SwapBuffer() noexcept override;

		void SpawnObject(const float posX, const float posY) noexcept; //spawn at location
		void SpawnObject(const float posX, const float posY, const glm::vec2& speed, const glm::vec2& dir) noexcept; //spawn and location and move with given speed and dir
	private:
		void ActivateObject() noexcept;
		GameObject* const m_pObjectToSpawn;
		const unsigned int m_SpawnDelayMs;
		unsigned int m_SpawnTimer;
		const bool m_DoesMove;
		bool m_CanStartMoving;
		bool m_WillSpawn;
	};
}


