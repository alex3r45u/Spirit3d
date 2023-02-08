#include "sppch.h"
#include "SphereCollider.h"

Spirit::Physics::SphereCollider::SphereCollider(const glm::vec3& center, float radius)
    : m_Center(center), m_Radius(radius), Collider(Type_Sphere)
{
}

CollisionPoints Spirit::Physics::SphereCollider::Collision(const TransformComponent* transform, const Collider* collider, const TransformComponent* colliderTransform) const
{
    return collider->Collision(colliderTransform, this, transform);
}

CollisionPoints Spirit::Physics::SphereCollider::Collision(const TransformComponent* transform, const AABBCollider* collider, const TransformComponent* colliderTransform) const
{
    throw 0;
}

CollisionPoints Spirit::Physics::SphereCollider::Collision(const TransformComponent* transform, const SphereCollider* collider, const TransformComponent* colliderTransform) const
{
    throw 0;
}
