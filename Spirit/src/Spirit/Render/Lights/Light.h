#pragma once
#include "Spirit/Render/Shader.h"

namespace Spirit::Render {
	class Light {
	public:
		Light() {}
		virtual void UploadUniforms(const std::shared_ptr<Shader>& shader) = 0;
		static int GetNoDirectionalLights()  { return s_NoDirectionalLights; }
		static int GetNoSpotLights()  { return s_NoSpotLights; }
		static int GetNoPointLights()  { return s_NoPointLights; }
	protected:
		static int s_NoDirectionalLights;
		static int s_NoSpotLights;
		static int s_NoPointLights;
	};
}