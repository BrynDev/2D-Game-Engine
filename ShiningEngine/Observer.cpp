#include "ShiningEnginePCH.h"
#include "Observer.h"

Shining::Observer::Observer()
	:m_SubjectCount{0}
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