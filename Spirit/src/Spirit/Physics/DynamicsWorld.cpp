#include "sppch.h"
#include "DynamicsWorld.h"
#include "Spirit/Scene/Components.h"

void Spirit::Physics::DynamicsWorld::AddRigidbody(const std::shared_ptr<RigidBody>& rigidbody)
{
}

void Spirit::Physics::DynamicsWorld::RemoveRigidbody()
{
}

void Spirit::Physics::DynamicsWorld::SetGravity(glm::vec3 gravity)
{
}

void Spirit::Physics::DynamicsWorld::Step(float dt)
{
	for (auto& obj : m_Objects) {
		auto o = std::static_pointer_cast<RigidBody>(obj);
		o->Force += o->Mass * m_Gravity;
		o->Velocity += o->Force / o->Mass * dt;
		o->Transform->Position += o->Velocity * dt;
		glm::quat rot = glm::angleAxis(
			glm::length(o->AngularVelocity) * dt,
			glm::length(o->AngularVelocity) == 0 ? glm::vec3(0, 0, 1)
			: glm::normalize(o->AngularVelocity)
		);
		o->Transform->Rotation = rot * o->Transform->Rotation;

		o->Force = glm::vec3(0.0f);
	}
}
