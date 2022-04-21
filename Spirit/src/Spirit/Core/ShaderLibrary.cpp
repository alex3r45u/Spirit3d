#include "sppch.h"
#include "ShaderLibrary.h"

void Spirit::ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Spirit::Render::Shader>& shader)
{
	SP_CORE_ASSERT(!Exists(name), "Shader already exists!");
	m_Shaders[name] = shader;
}

void Spirit::ShaderLibrary::Add(const std::shared_ptr<Spirit::Render::Shader>& shader)
{
	auto& name = shader->GetName();
	Add(name, shader);
}



std::shared_ptr<Spirit::Render::Shader> Spirit::ShaderLibrary::Load(const std::string& name, const std::string& vertPath, const std::string& fragPath)
{
	auto shader = Spirit::Render::Shader::Create(name, vertPath, fragPath);
	Add(name, shader);
	return shader;
}

std::shared_ptr<Spirit::Render::Shader> Spirit::ShaderLibrary::Get(const std::string& name)
{
	SP_CORE_ASSERT(Exists(name), "Shader not found!");
	return m_Shaders[name];
}

bool Spirit::ShaderLibrary::Exists(const std::string& name) const
{
	return m_Shaders.find(name) != m_Shaders.end();
}

