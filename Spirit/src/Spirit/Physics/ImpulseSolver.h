#pragma once
#include "Solver.h"
namespace Spirit::Physics {
	class ImpulseSolver : public Solver {
		virtual void Solve(
			const std::vector<Collision>& collisions,
			float dt) override;
	};
}