#include "sppch.h"
#include "PointLight.h"

void Spirit::Render::PointLight::UploadUniforms(const std::shared_ptr<Shader>& shader)
{
	std::string name = "pointLights[" + std::to_string(Light::s_NoPointLights) + "]";
	shader->SetFloat3(name + ".color", color.x, color.y, color.z);
	shader->SetFloat3(name + ".position", position.x, position.y, position.z);


	shader->SetFloat(name + ".k0", k0);
	shader->SetFloat(name + ".k1", k1);
	shader->SetFloat(name + ".k2", k2);


	Light::s_NoPointLights++;
}
