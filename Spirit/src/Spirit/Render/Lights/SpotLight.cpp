#include "sppch.h"
#include "SpotLight.h"

void Spirit::Render::SpotLight::UploadUniforms(const std::shared_ptr<Shader>& shader)
{
	std::string name = "spotLights[" + std::to_string(Light::s_NoSpotLights) + "]";
	shader->SetFloat3(name + ".color", color.x, color.y, color.z);
	shader->SetFloat3(name + ".position", position.x, position.y, position.z);
	shader->SetFloat3(name + ".direction", direction.x, direction.y, direction.z);

	shader->SetFloat(name + ".cutOff", cutOff);
	shader->SetFloat(name + ".outerCutOff", outerCutOff);

	shader->SetFloat(name + ".k0", k0);
	shader->SetFloat(name + ".k1", k1);
	shader->SetFloat(name + ".k2", k2);


	Light::s_NoSpotLights++;
}
