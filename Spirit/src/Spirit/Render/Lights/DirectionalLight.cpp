#include "sppch.h"
#include "DirectionalLight.h"



void Spirit::Render::DirectionalLight::UploadUniforms(const std::shared_ptr<Shader>& shader)
{
	std::string name = "directionalLights[" + std::to_string(Light::s_NoDirectionalLights) + "]";
	shader->SetFloat3(name + ".color", color.x, color.y, color.z);
	shader->SetFloat3(name + ".rotation", rotation.x, rotation.y, rotation.z);

	Light::s_NoDirectionalLights++;
}
