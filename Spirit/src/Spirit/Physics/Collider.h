#pragma once
#include <memory>
#include "CollisionPoints.h"

namespace Spirit {
	class TransformComponent;
}

namespace Spirit::Physics {
	class AABBCollider;
	class SphereCollider;
	class Collider {
	public:
		enum {
			Type_None = 0,
			Type_AABB,
			Type_Sphere
		};
		Collider(int type)
			: m_Type(type) {

		}
		Collider() = default;
		virtual CollisionPoints Collision(
			const TransformComponent* transform,
			const Collider* collider,
			const TransformComponent* colliderTransform) const = 0;

		virtual CollisionPoints Collision(
			const TransformComponent* transform,
			const AABBCollider* collider,
			const TransformComponent* colliderTransform) const = 0;

		virtual CollisionPoints Collision(
			const TransformComponent* transform,
			const SphereCollider* collider,
			const TransformComponent* colliderTransform) const = 0;

		inline const int const GetType() { return m_Type; }
	private:
		int m_Type;
	};
}