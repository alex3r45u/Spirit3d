#include "sppch.h"
#include "AABBCollider.h"

Spirit::Physics::AABBCollider::AABBCollider(const glm::vec3& minExtents, const glm::vec3& maxExtents)
	: m_MaxExtents(maxExtents), m_MinExtents(minExtents), Collider(Type_AABB)
{
	
}

CollisionPoints Spirit::Physics::AABBCollider::Collision(const TransformComponent* transform, const Collider* collider, const TransformComponent* colliderTransform) const
{
	return collider->Collision(colliderTransform, this, transform);
}

CollisionPoints Spirit::Physics::AABBCollider::Collision(const TransformComponent* transform, const AABBCollider* collider, const TransformComponent* colliderTransform) const
{
	return CollisionPoints();
}

CollisionPoints Spirit::Physics::AABBCollider::Collision(const TransformComponent* transform, const SphereCollider* collider, const TransformComponent* colliderTransform) const
{
	return CollisionPoints();
}

