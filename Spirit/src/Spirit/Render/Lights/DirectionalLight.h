#pragma once
#include "Light.h"
#include <glm/glm.hpp>

namespace Spirit::Render {
	class DirectionalLight : public Light {
	public:
		DirectionalLight() = default;
		DirectionalLight(const glm::vec3& direction, const glm::vec3& color) : direction(direction), color(color) {}

		virtual void UploadUniforms(const std::shared_ptr<Shader>& shader) override;

		glm::vec3 color;
		glm::vec3 direction;
	};
}