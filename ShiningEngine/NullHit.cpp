#include "ShiningEnginePCH.h"
#include "NullHit.h"

void Shining::NullHit::OnHit(GameObject* const /*pHitObject*/, const int /*damageTaken*/) const noexcept
{
	//empty
}


void Shining::NullHit::OnDeath(GameObject* const /*pDeadObject)*/) const noexcept
{
	//empty
}