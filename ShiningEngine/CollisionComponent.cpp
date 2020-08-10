#include "ShiningEnginePCH.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "GameObject.h"

Shining::NullCollision Shining::CollisionComponent::m_NullBehavior;

Shining::CollisionComponent::CollisionComponent(Shining::GameObject* const pOwner, const Shining::RenderComponent* const pComponent, const int tag, const bool isStatic)
	:CollisionComponent(pOwner, pComponent->GetSpriteWidth(), pComponent->GetSpriteHeight(), tag, isStatic)
{
}

Shining::CollisionComponent::CollisionComponent(Shining::GameObject* const pOwner, const int width, const int height, const int tag, const bool isStatic)
	:Component()
	, m_pOwner{pOwner}
	, m_pOwnerPos{ &(pOwner->GetPosition()) }
	, m_BoxWidth{ width }
	, m_BoxHeight{ height }
	, m_Tag{tag}
	, m_IsStatic{ isStatic }
	, m_pCollisionBehavior{&m_NullBehavior}
{
	//register to collision manager
	Shining::CollisionManager::GetInstance().RegisterCollisionComponent(this, tag);
}

const SDL_Rect Shining::CollisionComponent::GetBoundingBox() const noexcept
{
	return SDL_Rect{ int(m_pOwnerPos->x), int(m_pOwnerPos->y), m_BoxWidth, m_BoxHeight };
}

void Shining::CollisionComponent::Update(const float /*timeStep*/)
{
	SDL_Rect boundingBox{ int(m_pOwnerPos->x), int(m_pOwnerPos->y), m_BoxWidth, m_BoxHeight };
	const Shining::CollisionManager& instance{ Shining::CollisionManager::GetInstance() };

	for (const int targetTag : m_TagsToCollideWith) //for every tag that's relevant to this object
	{

		if (instance.IsColliding(boundingBox, m_Tag, targetTag, m_IsStatic))
		{
			ResolveCollision(targetTag);
			break;
		}
	}
	
}

void Shining::CollisionComponent::Render(const glm::vec2& /*pos*/)
{
	//can render hitboxes for testing maybe
	
}

void Shining::CollisionComponent::ResolveCollision(const int collidedTag) noexcept
{
	m_pCollisionBehavior->ResolveCollision(m_pOwner, collidedTag);
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

void Shining::CollisionComponent::AddTargetTags(const std::set<int>& targets) noexcept
{
	for (int tag : targets)
	{
		m_TagsToCollideWith.insert(tag);
	}
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

	m_pCollisionBehavior = pBehavior;
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