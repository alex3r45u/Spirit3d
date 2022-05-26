#include "sppch.h"
#include "MaterialLibrary.h"

void Spirit::MaterialLibrary::Add(const std::string& name, const std::shared_ptr<Render::Material>& material)
{
	SP_CORE_ASSERT(!Exists(name), "Material already exists!");
	m_Materials[name] = material;
}


std::shared_ptr<Spirit::Render::Material> Spirit::MaterialLibrary::Get(const std::string& name)
{
	SP_CORE_ASSERT(Exists(name), "Material not found!");
	return m_Materials[name];
}

bool Spirit::MaterialLibrary::Exists(const std::string& name) const
{
	return m_Materials.find(name) != m_Materials.end();
}

void Spirit::MaterialLibrary::Load(const std::string& name, const std::string& path)
{
	//TODO load out json
	//Add(name, shader);
	//return shader;
}
