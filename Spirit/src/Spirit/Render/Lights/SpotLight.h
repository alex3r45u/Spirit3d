#pragma once

#include "Light.h"

namespace Spirit::Render {
	class SpotLight : public Light {
	public:
		SpotLight() : k0(1.0f), k1(0.09f), k2(0.032f) {}
		virtual void UploadUniforms(const std::shared_ptr<Shader>& shader) override;



		float cutOff;
		float outerCutOff;

		float k0;
		float k1;
		float k2;

	};
}