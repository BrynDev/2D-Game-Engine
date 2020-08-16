#include "PickupCollision.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

void PickupCollision::ResolveCollision(Shining::GameObject* const pObject, const int collidedTag) const noexcept
{
	switch (collidedTag)
	{
	case int(CollisionTags::player):
		pObject->SetActive(false);
		Shining::AudioPlayer::GetInstance().PlaySoundEffect("PickupSound.wav");
		break;
	default:
		break;
	}
}