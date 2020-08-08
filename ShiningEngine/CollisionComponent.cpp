#include "ShiningEnginePCH.h"
#include "CollisionComponent.h"
#include "CollisionManager.h"


Shining::CollisionComponent::CollisionComponent(const glm::vec2* pPosition, const Shining::RenderComponent* const pComponent, const int tag, const bool isStatic)
	:CollisionComponent(pPosition, pComponent->GetSpriteWidth(), pComponent->GetSpriteHeight(), tag, isStatic)
{
}

Shining::CollisionComponent::CollisionComponent(const glm::vec2* pPosition, const int width, const int height, const int tag, const bool isStatic)
	:Component()
	, m_pOwnerPos{ pPosition }
	, m_BoxWidth{ width }
	, m_BoxHeight{ height }
	, m_Tag{tag}
	, m_IsStatic{ isStatic }
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
	for (const int targetTag : m_TagsToCollideWith)
	{
		if (instance.IsColliding(boundingBox, targetTag, m_IsStatic))
		{
			//do collision resolution
			std::cout << "Collision\n"; //TEST
			break;
		}
	}
	
}

void Shining::CollisionComponent::Render(const glm::vec2& /*pos*/)
{
	//can render hitboxes for testing maybe
	
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

Shining::CollisionComponent::~CollisionComponent()
{
	Shining::CollisionManager::GetInstance().RemoveCollisionComponent(this, m_Tag);
}