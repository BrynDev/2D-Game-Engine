#pragma once
#include "Component.h"

namespace Shining
{
	class Shining::GameObject;
	class FPSComponent final : public Shining::Component
	{
	public:
		//this component needs to communicate with another component, so it needs to know its owner
		FPSComponent(const Shining::GameObject* pOwner);
		virtual ~FPSComponent() = default;

		virtual void Update() override;
		virtual void Render(const glm::vec3& pos) /*const*/ override;

		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
	private:
		const Shining::GameObject* m_pOwner;
		const int m_MsPerFrame;
		int m_NrFramesRendered;
		int m_ElapsedTimeMs;
	};
}

