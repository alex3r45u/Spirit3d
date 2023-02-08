#pragma once
#include "Collider.h"
#include "glm/glm.hpp"
namespace Spirit::Physics {
	class SphereCollider : public Collider {
	public:
		SphereCollider(const glm::vec3& center, float radius);
		SphereCollider() = default;

		inline const glm::vec3& GetCenter() const { return m_Center; }
		inline const float GetRadius() const { return m_Radius; }

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
	private:
		glm::vec3 m_Center;
		float m_Radius;
	};
}