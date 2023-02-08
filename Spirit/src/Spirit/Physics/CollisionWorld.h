#pragma once
#include <vector>
#include <memory>
#include "PhysicsObject.h"
#include "Solver.h"
namespace Spirit::Physics {
	class CollisionWorld {
	protected:
		std::vector<std::shared_ptr<PhysicsObject>> m_Objects;
		std::vector<std::shared_ptr<Solver>> m_Solvers;

		
	public:
		void ResolveCollisions(float dt);

		void AddCollisionObject(const std::shared_ptr<PhysicsObject>& object);
		void RemoveCollisionObject(const std::shared_ptr<PhysicsObject>& object);

		void AddSolver(const std::shared_ptr<Solver> solver);
		void RemoveSolver(const std::shared_ptr<Solver> solver);
	};
}