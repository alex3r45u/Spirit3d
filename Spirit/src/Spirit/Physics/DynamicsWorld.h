#pragma once
#include "CollisionWorld.h"
#include <glm/glm.hpp>
#include "RigidBody.h"
namespace Spirit::Physics {
	class DynamicsWorld : public CollisionWorld {
	private:
		glm::vec3 m_Gravity = glm::vec3(0.0f, -9.81f, 0.0f);

	public:
		void AddRigidbody(const std::shared_ptr<RigidBody>& rigidbody);
		void RemoveRigidbody();
		void SetGravity(glm::vec3 gravity);
		glm::vec3 GetGravity() { return m_Gravity; }
		void Step(float dt);
	};
}