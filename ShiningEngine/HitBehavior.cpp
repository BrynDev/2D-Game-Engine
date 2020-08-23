#include "ShiningEnginePCH.h"
#include "HitBehavior.h"

void Shining::HitBehavior::IncreaseInstanceCount() noexcept
{
	++m_InstanceCount;
}

bool Shining::HitBehavior::DecreaseInstanceCount() noexcept //returns true if the instance count is 0, the owner object then deletes this
{
	--m_InstanceCount;
	return(m_InstanceCount <= 0);
}