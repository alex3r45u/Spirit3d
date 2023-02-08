#pragma once
#include <glm/glm.hpp>
struct CollisionPoints {
	glm::vec3 A;
	glm::vec3 B;
	glm::vec3 Normal;
	float Depth;
	bool HasCollision;
};