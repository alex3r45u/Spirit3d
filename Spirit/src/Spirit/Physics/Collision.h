#pragma once
#include "CollisionPoints.h"
#include <memory>
namespace Spirit::Physics {
	class PhysicsObject;
	struct Collision {
		std::shared_ptr<PhysicsObject> ObjA;
		std::shared_ptr<PhysicsObject> ObjB;
		CollisionPoints Points;
		Collision(const std::shared_ptr<PhysicsObject>& objA,
			const std::shared_ptr<PhysicsObject>& objB,
			CollisionPoints points) {
			ObjA = objA;
			ObjB = objB;
			Points = points;
		}
	};
}