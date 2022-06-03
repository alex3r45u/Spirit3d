#include "sppch.h"
#include "MaterialLibrary.h"

void Spirit::MaterialLibrary::Add(const std::string& name, const std::shared_ptr<Render::Material>& material)
{
	SP_CORE_ASSERT(!Exists(name), "Material already exists!");
	m_Materials[name] = material;
}


std::shared_ptr<Spirit::Render::Material> Spirit::MaterialLibrary::Get(const std::string& path)
{
	if (!Exists(path)) {
		Load(path, path);
	}
	return m_Materials[path];
}

bool Spirit::MaterialLibrary::Exists(const std::string& path) const
{
	return m_Materials.find(path) != m_Materials.end();
}

void Spirit::MaterialLibrary::Load(const std::string& name, const std::string& path)
{
	//TODO load out json
	//Add(name, shader);
	//return shader;
}
