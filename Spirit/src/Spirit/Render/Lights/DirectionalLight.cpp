#include "sppch.h"
#include "DirectionalLight.h"



void Spirit::Render::DirectionalLight::UploadUniforms(const std::shared_ptr<Shader>& shader)
{
	std::string name = "u_DirectionalLights[" + std::to_string(Light::s_NoDirectionalLights) + "]";
	shader->SetFloat3(name + ".Light.Color", Color.x, Color.y, Color.z);
	shader->SetFloat(name + ".Light.Intensity", Intensity);
	shader->SetFloat3(name + ".Direction", Forward.x, Forward.y, Forward.z);

	Light::s_NoDirectionalLights++;
}
