#pragma once
#include "Light.h"

namespace Spirit::Render {
	class PointLight : public Light {
	public:
		PointLight() = default;

		virtual void UploadUniforms(const std::shared_ptr<Shader>& shader) override;
		float Radius;
	};
}