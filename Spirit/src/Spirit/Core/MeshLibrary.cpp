#include "sppch.h"
#include "MeshLibrary.h"

void Spirit::MeshLibrary::Add(const std::string& name, const std::shared_ptr<Render::Mesh>& mesh)
{
	SP_CORE_ASSERT(!Exists(name), "Material already exists!");
	m_Meshes[name] = mesh;
}


const std::shared_ptr<Spirit::Render::Mesh> Spirit::MeshLibrary::Get(const std::string& name)
{
	SP_CORE_ASSERT(Exists(name), "Mesh not found!");
	return m_Meshes[name];
}

bool Spirit::MeshLibrary::Exists(const std::string& name) const
{
	return m_Meshes.find(name) != m_Meshes.end();
}

void Spirit::MeshLibrary::Load(const std::string& name, const std::string& path)
{
	std::shared_ptr<Spirit::Render::Mesh> mesh = std::make_shared<Spirit::Render::Mesh>(path);
	Add(name, mesh);
}
