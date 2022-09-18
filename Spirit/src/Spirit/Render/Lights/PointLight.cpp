#include "sppch.h"
#include "PointLight.h"

void Spirit::Render::PointLight::UploadUniforms(const std::shared_ptr<Shader>& shader)
{
	std::string name = "u_PointLights[" + std::to_string(Light::s_NoPointLights) + "]";
	shader->SetFloat3(name + ".Light.Color", Color.x, Color.y, Color.z);
	shader->SetFloat3(name + ".Position", Position.x, Position.y, Position.z);
	shader->SetFloat(name + ".Light.Intensity", Intensity);
	shader->SetFloat(name + ".Radius", Radius);


	Light::s_NoPointLights++;
}
