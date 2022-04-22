#pragma once
#include "Light.h"
#include <glm/glm.hpp>

namespace Spirit::Render {
	class DirectionalLight : public Light {
	public:
		DirectionalLight() {}
		DirectionalLight(const glm::vec3& rotation, const glm::vec3& color) : rotation(rotation), color(color) {}

		virtual void UploadUniforms(const std::shared_ptr<Shader>& shader) override;

		glm::vec3 color;
		glm::vec3 rotation;
	};
}