#pragma once
#include "Collider.h"
#include "glm/glm.hpp"
namespace Spirit::Physics {
	class AABBCollider : public Collider {
	public:
		AABBCollider(const glm::vec3& minExtents, const glm::vec3& maxExtents);
		AABBCollider() = default;
		virtual CollisionPoints Collision(
			const TransformComponent* transform,
			const Collider* collider,
			const TransformComponent* colliderTransform) const override;

		virtual CollisionPoints Collision(
			const TransformComponent* transform,
			const AABBCollider* collider,
			const TransformComponent* colliderTransform) const override;

		virtual CollisionPoints Collision(
			const TransformComponent* transform,
			const SphereCollider* collider,
			const TransformComponent* colliderTransform) const override;

		inline const glm::vec3& const GetMinExtents() { return m_MinExtents; }
		inline const glm::vec3& const GetMaxExtents() { return m_MaxExtents; }
	private:
		glm::vec3 m_MinExtents;
		glm::vec3 m_MaxExtents;
	};
}