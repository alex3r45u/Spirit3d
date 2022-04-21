#pragma once
#include "Light.h"
#include <memory>
#include <vector>


namespace Spirit::Render {
	enum class LightTypes {
		None = 0,
		PointLight,
		DirectionalLight,
		SpotLight,
	};


	class LightManager {
	public:
		static void Submit(std::shared_ptr<Light> light, LightTypes type);
		static void SetUniforms();
	private:
		static std::vector<std::shared_ptr<Light>> s_Lights;

		static int s_PointLightCount;
		static int s_DirectionalLightCount;
		static int s_SpotLightCount;
	};
}