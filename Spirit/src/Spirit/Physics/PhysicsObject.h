#pragma once
#include "Spirit/Scene/Entity.h"
#include <glm/glm.hpp>
#include "Collider.h"
#include <functional>
namespace Spirit::Physics {
	class Collision;
	struct PhysicsObject {
	public:
		Collider* Collider;
		TransformComponent* Transform;

		bool IsDynamic;
		bool IsSimulated;
		bool IsTrigger;
	protected:
		std::function<void(Collision&, float)> OnCollision;

	};
}