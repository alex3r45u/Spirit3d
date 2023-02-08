#include "sppch.h"
#include "ImpulseSolver.h"
#include "RigidBody.h"

void Spirit::Physics::ImpulseSolver::Solve(const std::vector<Collision>& collisions, float dt)
{
	for (auto& a : collisions) {
		std::shared_ptr<RigidBody> aBody = a.ObjA ? std::static_pointer_cast<RigidBody>(a.ObjA) : nullptr;
		std::shared_ptr<RigidBody> bBody = a.ObjB->IsDynamic ? std::static_pointer_cast<RigidBody>(a.ObjB) : nullptr;

		glm::vec3 aVel = aBody ? aBody->Velocity : glm::vec3(0.0f);
		glm::vec3 bVel = bBody ? bBody->Velocity : glm::vec3(0.0f);
		glm::vec3 rVel = bVel - aVel;
		float  nSpd = glm::dot(rVel, a.Points.Normal);

		float aInvMass = aBody ? 1/aBody->Mass: 1.0f;
		float bInvMass = bBody ? 1/bBody->Mass : 1.0f;


		if (nSpd >= 0)
			continue;

		float e = (aBody ? aBody->Restitution : 1.0f)
			* (bBody ? bBody->Restitution : 1.0f);

		float j = -(1.0f + e) * nSpd / (aInvMass + bInvMass);

		glm::vec3 impluse = j * a.Points.Normal;

		if (aBody ? aBody->IsSimulated : false) {
			aVel -= impluse * aInvMass;
		}

		if (bBody ? bBody->IsSimulated : false) {
			bVel += impluse * bInvMass;
		}

		// Friction

		rVel = bVel - aVel;
		nSpd = glm::dot(rVel, a.Points.Normal);

		glm::vec3 tangent = rVel - nSpd * a.Points.Normal;

		if (glm::length(tangent) > 0.0001f) { // safe normalize
			tangent = glm::normalize(tangent);
		}

		float fVel = glm::dot(rVel, tangent);

		float aSF = aBody ? aBody->StaticFriction : 0.0f;
		float bSF = bBody ? bBody->StaticFriction : 0.0f;
		float aDF = aBody ? aBody->DynamicFriction : 0.0f;
		float bDF = bBody ? bBody->DynamicFriction : 0.0f;
		float mu = (float)glm::vec2(aSF, bSF).length();

		float f = -fVel / (aInvMass + bInvMass);

		glm::vec3 friction;
		if (abs(f) < j * mu) {
			friction = f * tangent;
		}

		else {
			mu = glm::length(glm::vec2(aDF, bDF));
			friction = -j * tangent * mu;
		}

		if (aBody ? aBody->IsSimulated : false) {
			aBody->Velocity = aVel - friction * aInvMass;
		}

		if (bBody ? bBody->IsSimulated : false) {
			bBody->Velocity = bVel + friction * bInvMass;
		}
	}
}
