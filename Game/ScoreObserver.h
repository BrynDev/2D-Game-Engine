#pragma once
#include "Observer.h"

namespace Shining //class forward declaration of a class in a namespace
{
	class TextComponent;
	class GameObject;
};

class ScoreObserver final : public Shining::Observer 
{
public:
	explicit ScoreObserver(Shining::TextComponent* const pScoreText);
	virtual ~ScoreObserver() = default;

	virtual void Notify(Shining::GameObject* const pSubject, const int eventID, void* pData) noexcept override;
private:
	Shining::TextComponent* const m_pScoreText;
	int m_Score;
	int m_ExtraLifeCount;
	int m_GemPickupStreak;
	const int m_GemPickupStreakMax;
};

