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


void Spirit::Render::ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader)
{
	SP_CORE_ASSERT(!Exists(name), "Shader already exists!");
	m_Shaders[name] = shader;
}

void Spirit::Render::ShaderLibrary::Add(const std::shared_ptr<Shader>& shader)
{
	auto& name = shader->GetName();
	Add(name, shader);
}



std::shared_ptr<Spirit::Render::Shader> Spirit::Render::ShaderLibrary::Load(const std::string& name, const std::string& vertPath, const std::string& fragPath)
{
	auto shader = Shader::Create(name, vertPath, fragPath);
	Add(name, shader);
	return shader;
}

std::shared_ptr<Spirit::Render::Shader> Spirit::Render::ShaderLibrary::Get(const std::string& name)
{
	SP_CORE_ASSERT(Exists(name), "Shader not found!");
	return m_Shaders[name];
}

bool Spirit::Render::ShaderLibrary::Exists(const std::string& name) const
{
	return m_Shaders.find(name) != m_Shaders.end();
}

