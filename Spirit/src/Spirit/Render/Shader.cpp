#include "sppch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Spirit/Platform/OpenGl/OpenGlShader.h"

std::shared_ptr<Spirit::Render::Shader> Spirit::Render::Shader::Create(const std::string& name, const std::filesystem::path& vertPath, const std::filesystem::path& fragPath)
{
	switch (Renderer::GetAPI())
	{
	case RenderAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGl:  return std::make_shared<OpenGlShader>(name, vertPath, fragPath);
	}

	SP_CORE_ASSERT(false, "Unknown RenderAPI!");
	return nullptr;
}

void Spirit::Render::Shader::SetFloat2(const std::string& name, glm::vec2 vec2)
{
	SetFloat2(name, vec2.x, vec2.y);
}

void Spirit::Render::Shader::SetFloat3(const std::string& name, glm::vec3 vec3)
{
	SetFloat3(name, vec3.x, vec3.y, vec3.z);
}

void Spirit::Render::Shader::SetFloat4(const std::string& name, glm::vec4 vec4)
{
	SetFloat4(name, vec4.x, vec4.y, vec4.z, vec4.w);
}
