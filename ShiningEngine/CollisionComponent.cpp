#include "ShiningEnginePCH.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "GameObject.h"

Shining::NullCollision Shining::CollisionComponent::m_NullBehavior;

Shining::CollisionComponent::CollisionComponent(Shining::GameObject* const pOwner, const Shining::RenderComponent* const pComponent, const int tag, const bool hasWorldCollision, const bool canBreakTiles)
	:CollisionComponent(pOwner, pComponent->GetSpriteWidth(), pComponent->GetSpriteHeight(), tag, hasWorldCollision, canBreakTiles)
{
}

Shining::CollisionComponent::CollisionComponent(Shining::GameObject* const pOwner, const int width, const int height, const int tag, const bool hasWorldCollision, const bool canBreakTiles)
	:Component()
	, m_pOwner{pOwner}
	, m_pCollisionBehavior{ &m_NullBehavior }
	, m_BoxWidth{ width }
	, m_BoxHeight{ height }
	, m_Tag{tag}
	, m_CanCollideWithWorld{hasWorldCollision}
	, m_CanBreakTiles{ canBreakTiles }
{
	//this collider will be registered to the collision manager when the scene it belongs to becomes active
}

const SDL_Rect Shining::CollisionComponent::GetBoundingBox() const noexcept
{
	const glm::vec2& ownerPos{ m_pOwner->GetNextPosition() }; //used to check if object will collide next frame
	return SDL_Rect{ int(ownerPos.x), int(ownerPos.y), m_BoxWidth, m_BoxHeight };
}

void Shining::CollisionComponent::Update(const float /*timeStep*/)
{
	SDL_Rect boundingBox{ GetBoundingBox() };
	Shining::CollisionManager& instance{ Shining::CollisionManager::GetInstance() };

	//collide with world
	if (m_CanCollideWithWorld)
	{
		if (instance.HandleWorldCollision(boundingBox, m_CanBreakTiles))
		{
			ResolveWorldCollision();

			if (!m_CanBreakTiles)
			{
				//if colliding with a tile and you can't break through it, get blocked
				m_pOwner->GetComponent<Shining::PhysicsComponent>()->BlockMovement();
			}
		}
	}

	//collide with other objects
	for (const int targetTag : m_TagsToCollideWith) //for every tag that's relevant to this object
	{
		Shining::CollisionComponent* const pCollidingObject{ instance.GetCollidingObject(boundingBox, targetTag) };
		if (pCollidingObject == nullptr)
		{
			//no collision happened
			continue;
		}

		ResolveCollision(targetTag);
		pCollidingObject->ResolveCollision(m_Tag);
	}
}

void Shining::CollisionComponent::Render(const glm::vec2& /*pos*/) const
{
	//empty
}

void Shining::CollisionComponent::ResolveCollision(const int collidedTag) noexcept
{
	m_pCollisionBehavior->ResolveCollision(m_pOwner, collidedTag);
}

void Shining::CollisionComponent::ResolveWorldCollision() noexcept
{
	m_pCollisionBehavior->ResolveWorldCollision(m_pOwner);
}

void Shining::CollisionComponent::SwapBuffer() noexcept
{
	//empty
}

void Shining::CollisionComponent::AddTargetTag(const int tag) noexcept
{
	if (tag == m_Tag)
	{
		return;
	}

	m_TagsToCollideWith.insert(tag);
}

void Shining::CollisionComponent::RemoveTargetTag(const int tag) noexcept
{
	m_TagsToCollideWith.erase(tag);
}

void Shining::CollisionComponent::SetBehavior(CollisionBehavior* const pBehavior) noexcept
{
	if (m_pCollisionBehavior != &m_NullBehavior) //make sure not to call delete on the null behavior
	{
		if (m_pCollisionBehavior->DecreaseInstanceCount()) //if this behavior object isn't owned by anything anymore, delete it
		{
			delete m_pCollisionBehavior;
		}
	}

	pBehavior->IncreaseInstanceCount();
	m_pCollisionBehavior = pBehavior;
}

const int Shining::CollisionComponent::GetTag() const noexcept
{
	return m_Tag;
}

Shining::CollisionComponent::~CollisionComponent()
{
	Shining::CollisionManager::GetInstance().RemoveCollisionComponent(this, m_Tag);

	if (m_pCollisionBehavior != &m_NullBehavior) //make sure not to call delete on the null behavior
	{
		if (m_pCollisionBehavior->DecreaseInstanceCount())
		{
			delete m_pCollisionBehavior;
		}
	}
}