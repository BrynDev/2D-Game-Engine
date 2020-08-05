#include "ShiningEnginePCH.h"
#include "Observer.h"

Shining::Observer::Observer(Shining::GameObject* pObjectToModify)
	:m_pObjectToModify{pObjectToModify}
	,m_SubjectCount{0}
{
}

bool Shining::Observer::DecreaseSubjectCount() noexcept
{
	--m_SubjectCount;
	//if this observer isn't observing anything, return true so the owner can delete it
	return (m_SubjectCount <= 0);
}

void Shining::Observer::IncreaseSubjectCount() noexcept
{
	++m_SubjectCount;
}

void Shining::Observer::SetTargetObject(GameObject* pObjectToModify) noexcept
{
	m_pObjectToModify = pObjectToModify;
}