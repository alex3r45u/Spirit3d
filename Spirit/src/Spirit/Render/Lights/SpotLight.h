#pragma once

#include "Light.h"

namespace Spirit::Render {
	class SpotLight : public Light {
	public:
		SpotLight() {}
		SpotLight(
			const glm::vec3& color,
			const glm::vec3& position,
			const glm::vec3& direction,

			float cutOff,
			float outerCutOff,

			float k0,
			float k1,
			float k2
		) : color(color), position(position), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff), k0(k0), k1(k1), k2(k2)
		{

		}

		virtual void UploadUniforms(const std::shared_ptr<Shader>& shader) override;


		glm::vec3 color;
		glm::vec3 position;
		glm::vec3 direction;

		float cutOff;
		float outerCutOff;

		float k0;
		float k1;
		float k2;

	};
}