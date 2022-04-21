#include "sppch.h"
#include "LightManager.h"


std::vector<std::shared_ptr<Spirit::Render::Light>> Spirit::Render::LightManager::s_Lights = std::vector<std::shared_ptr<Spirit::Render::Light>>();

int Spirit::Render::LightManager::s_DirectionalLightCount = 0;
int Spirit::Render::LightManager::s_SpotLightCount = 0;
int Spirit::Render::LightManager::s_PointLightCount = 0;

void Spirit::Render::LightManager::Submit(std::shared_ptr<Light> light, LightTypes type)
{
	s_Lights.push_back(light);
}

void Spirit::Render::LightManager::SetUniforms()
{
	for (auto l : s_Lights) {
		l->UploadUniforms();
	}
}
