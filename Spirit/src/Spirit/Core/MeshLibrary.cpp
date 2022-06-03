#include "sppch.h"
#include "MeshLibrary.h"

void Spirit::MeshLibrary::Add(const std::string& name, const std::shared_ptr<Render::Mesh>& mesh)
{
	SP_CORE_ASSERT(!Exists(name), "Material already exists!");
	m_Meshes[name] = mesh;
}


std::shared_ptr<Spirit::Render::Mesh> Spirit::MeshLibrary::Get(const std::string& path)
{
	if (!Exists(path)) {
		Load(path, path);
	}
	return m_Meshes[path];
}

bool Spirit::MeshLibrary::Exists(const std::string& path) const
{
	return m_Meshes.find(path) != m_Meshes.end();
}

void Spirit::MeshLibrary::Load(const std::string& name, const std::string& path)
{
	std::shared_ptr<Spirit::Render::Mesh> mesh = std::make_shared<Spirit::Render::Mesh>(path);
	Add(name, mesh);
}
