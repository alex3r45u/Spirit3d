#pragma once
#include "Spirit/Render/Shader.h"
#include <glm/glm.hpp>

namespace Spirit::Render {
	class Light {
	public:
		Light() : color(glm::vec3(1.0f)) {}
		virtual void UploadUniforms(const std::shared_ptr<Shader>& shader) = 0;
		static int GetNoDirectionalLights()  { return s_NoDirectionalLights; }
		static int GetNoSpotLights()  { return s_NoSpotLights; }
		static int GetNoPointLights()  { return s_NoPointLights; }
		static void ResetNoLights();
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 color;

	protected:
		static int s_NoDirectionalLights;
		static int s_NoSpotLights;
		static int s_NoPointLights;
	};
}