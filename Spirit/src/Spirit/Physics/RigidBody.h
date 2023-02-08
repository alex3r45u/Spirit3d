#pragma once
#include <glm/glm.hpp>
#include "PhysicsObject.h"
namespace Spirit::Physics {
	struct RigidBody : public PhysicsObject {
		float Mass;
		glm::vec3 Velocity;
		glm::vec3 Force;

	
		glm::vec3 AngularVelocity;
		bool TakesGravity;

		float Restitution;
		float StaticFriction;
		float DynamicFriction;
	};
}