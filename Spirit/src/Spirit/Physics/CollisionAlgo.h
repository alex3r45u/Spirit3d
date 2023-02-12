#pragma once
#include "CollisionPoints.h"

namespace Spirit::Physics {
	class CollisionAlgo {
	public:
		static CollisionPoints FindSphereSphereCollision();
		static CollisionPoints FineSphereAABBCollision();
		static CollisionPoints FindAABBAABBCollision();
	};
}