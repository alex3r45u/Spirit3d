#include "sppch.h"
#include "CollisionWorld.h"

void Spirit::Physics::CollisionWorld::ResolveCollisions(float dt)
{
	std::vector<Collision> collisions;
	for (auto& a : m_Objects) {
		for (auto& b : m_Objects) {
			if (a == b) break;
			if (!a->Collider || !b->Collider) continue;

			CollisionPoints points = a->Collider->Collision(a->Transform, b->Collider, b->Transform);

			if (points.HasCollision) {
				collisions.emplace_back(a, b, points);
			}
		}
	}

	for (auto& solver : m_Solvers) {
		solver->Solve(collisions, dt);
	}
}

void Spirit::Physics::CollisionWorld::AddCollisionObject(const std::shared_ptr<PhysicsObject>& object)
{
	m_Objects.push_back(object);
}

void Spirit::Physics::CollisionWorld::RemoveCollisionObject(const std::shared_ptr<PhysicsObject>& object)
{
	std::remove(m_Objects.begin(), m_Objects.end(), object);
}

void Spirit::Physics::CollisionWorld::AddSolver(const std::shared_ptr<Solver> solver)
{
	m_Solvers.push_back(solver);
}

void Spirit::Physics::CollisionWorld::RemoveSolver(const std::shared_ptr<Solver> solver)
{
	std::remove(m_Solvers.begin(), m_Solvers.end(), solver);
}

