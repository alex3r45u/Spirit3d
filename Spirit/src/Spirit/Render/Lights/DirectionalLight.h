#pragma once
#include "Light.h"
#include <glm/glm.hpp>

namespace Spirit::Render {
	class DirectionalLight : public Light {
	public:
		DirectionalLight() = default;

		virtual void UploadUniforms(const std::shared_ptr<Shader>& shader) override;

	};
}