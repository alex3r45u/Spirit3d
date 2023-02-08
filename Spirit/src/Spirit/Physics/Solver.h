#pragma once
#include <vector>
#include "Collision.h"
namespace Spirit::Physics {
	class Solver {
	public:
		virtual void Solve(
			const std::vector<Collision>& collisions,
			float dt) = 0;
	};
}