#pragma once
#include "Spirit/Render/Shader.h"
#include <glm/glm.hpp>

namespace Spirit::Render {
	class Light {
	public:
		Light() = default;
		virtual void UploadUniforms(const std::shared_ptr<Shader>& shader) = 0;
		static int GetNoDirectionalLights()  { return s_NoDirectionalLights; }
		static int GetNoSpotLights()  { return s_NoSpotLights; }
		static int GetNoPointLights()  { return s_NoPointLights; }
		static void ResetNoLights();
		glm::vec3 Position;
		glm::vec3 Direction;
		glm::vec3 Forward;
		glm::vec3 Color;
		float Intensity;

	protected:
		static int s_NoDirectionalLights;
		static int s_NoSpotLights;
		static int s_NoPointLights;
	};
}