#pragma once
#include "Observer.h"

//class forward declaration of a namespace class
namespace Shining
{
	class TextComponent;
}

class LifeObserver final : public Shining::Observer
{
public:
	LifeObserver(Shining::TextComponent* const pLivesText);
	virtual ~LifeObserver() = default;
	
	virtual void Notify(Shining::GameObject* const pSubject, const int eventID, void* pData) noexcept override;
private:
	Shining::TextComponent* const m_pLivesText;
};

