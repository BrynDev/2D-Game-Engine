#include "ShiningEnginePCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "ShiningEngine.h"



Shining::FPSComponent::FPSComponent(const Shining::GameObject* pOwner)
	:m_pOwner{pOwner}
	, m_MsPerFrame{ShiningEngine::GetMsPerFrame()}
	, m_NrFramesRendered{}
	, m_ElapsedTimeMs{}
{
}

void Shining::FPSComponent::Update()
{
	m_ElapsedTimeMs += m_MsPerFrame;
	//++m_NrFramesRendered;
	if (m_ElapsedTimeMs >= 1000) //1 second
	{
		m_ElapsedTimeMs -= 1000;
		std::string newFPSText{ std::to_string(m_NrFramesRendered) + " FPS" };
		m_pOwner->GetComponent<TextComponent>()->SetText(newFPSText);
		m_NrFramesRendered = 0;
	}	
}


void Shining::FPSComponent::Render(const glm::vec3& /*pos*/) /*const*/
{
	++m_NrFramesRendered;
}