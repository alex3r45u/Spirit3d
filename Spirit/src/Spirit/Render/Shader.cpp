#include "sppch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Spirit/Platform/OpenGl/OpenGlShader.h"

std::shared_ptr<Spirit::Render::Shader> Spirit::Render::Shader::Create(const std::string& name, const std::string& vertPath, const std::string& fragPath)
{
	switch (Renderer::GetAPI())
	{
	case RenderAPI::API::None:    SP_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
	case RenderAPI::API::OpenGl:  return std::make_shared<OpenGlShader>(name, vertPath, fragPath);
	}

	SP_CORE_ASSERT(false, "Unknown RenderAPI!");
	return nullptr;
}
