#include "PickupCollision.h"
#include "Enums.h"
#include "ShiningEnginePCH.h"

PickupCollision::PickupCollision(const bool isGem)
	:m_IsGem{isGem}
{
}

void PickupCollision::ResolveCollision(Shining::GameObject* const pOwnerObject, const int collidedTag) const noexcept
{
	switch (collidedTag)
	{
	case int(CollisionTags::player):
		pOwnerObject->SetActive(false);
		if (m_IsGem)
		{
			Shining::AudioPlayer::GetInstance().PlaySoundEffect("PickupSound.wav");
		}
		else 
		{
			Shining::AudioPlayer::GetInstance().PlaySoundEffect("GoldPickup.wav");
		}
		break;
	case int(CollisionTags::enemy):
		pOwnerObject->SetActive(false);
		break;
	default:
		break;
	}
}

void PickupCollision::ResolveWorldCollision(Shining::GameObject* const /*pOwnerObject*/) const noexcept
{
	//pickups dont have world collision
}