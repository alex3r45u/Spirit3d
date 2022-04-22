#include "sppch.h"
#include "LightManager.h"



std::vector<std::shared_ptr<Spirit::Render::Light>> Spirit::Render::LightManager::s_Lights = std::vector<std::shared_ptr<Light>>();

int Spirit::Render::LightManager::s_DirectionalLightCount = 0;
int Spirit::Render::LightManager::s_SpotLightCount = 0;
int Spirit::Render::LightManager::s_PointLightCount = 0;

std::shared_ptr<Spirit::Render::Shader> Spirit::Render::LightManager::s_Shader = nullptr;

void Spirit::Render::LightManager::Start(const std::shared_ptr<Shader>& shader)
{
	s_PointLightCount = 0;
	s_SpotLightCount = 0;
	s_DirectionalLightCount = 0;

	s_Shader = shader;
}

void Spirit::Render::LightManager::End()
{
	SetUniforms();
	s_Shader->SetInt("u_NoDirectionalLights", Light::GetNoDirectionalLights());
	s_Shader->SetInt("u_NoSpotLights", Light::GetNoSpotLights());
	s_Shader->SetInt("u_NoPointLights", Light::GetNoPointLights());
}

void Spirit::Render::LightManager::Submit(std::shared_ptr<Light> light)
{
	s_Lights.push_back(light);
}

void Spirit::Render::LightManager::SetUniforms()
{
	s_Shader->Bind();
	for (auto l : s_Lights) {
		l->UploadUniforms(s_Shader);
	}
}
