#pragma once
#include "Light.h"
#include <memory>
#include <vector>
#include "Spirit/Render/Shader.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "Spirit/Scene/Components.h"

namespace Spirit::Render {



	class LightManager {
	public:
		static void Start(const std::shared_ptr<Shader>& shader);
		static void End();
		static void Submit(std::shared_ptr<Light> light, TransformComponent& transform);
	private:
		static void SetUniforms();
		static std::shared_ptr<Shader> s_Shader;
		static std::vector<std::shared_ptr<Light>> s_Lights;
		
	};
}