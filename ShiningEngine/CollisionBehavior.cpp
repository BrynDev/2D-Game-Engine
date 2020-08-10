#include "ShiningEnginePCH.h"
#include "CollisionBehavior.h"

void Shining::CollisionBehavior::IncreaseInstanceCount() noexcept
{
	++m_InstanceCount;
}
bool Shining::CollisionBehavior::DecreaseInstanceCount() noexcept
{
	--m_InstanceCount;
	return (m_InstanceCount <= 0); //if no more instances, return true and the owner deletes this
}
