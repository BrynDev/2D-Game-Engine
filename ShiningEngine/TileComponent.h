#pragma once
#include "Component.h"
#include <vector>

namespace Shining
{
	class TileComponent final : public Shining::Component
	{
	public:
		TileComponent(const std::string& path, const int tileWidth, const int tileHeight, const int nrCols, const int nrRows);

		virtual void Render(const glm::vec3& pos) /*const*/ override;
		virtual void Update(const float timeStep) override;
		virtual ~TileComponent() = default;
	private:
	};
}


