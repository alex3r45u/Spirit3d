#include "sppch.h"
#include "AssetLibrary.h"

Spirit::AssetRegistry<Spirit::Render::Mesh> Spirit::AssetLibrary::m_MeshRegistry;
Spirit::AssetRegistry<Spirit::Render::Shader> Spirit::AssetLibrary::m_ShaderRegistry;
Spirit::AssetRegistry<Spirit::Render::Material> Spirit::AssetLibrary::m_MaterialRegistry;

void Spirit::AssetLibrary::Init()
{
	m_MeshRegistry = Spirit::AssetRegistry<Spirit::Render::Mesh>([](std::vector<std::string> l) {
		return std::make_shared<Spirit::Render::Mesh>(l.at(0));
		});
	m_ShaderRegistry = Spirit::AssetRegistry<Spirit::Render::Shader>([](std::vector<std::string> l) {
		return Spirit::Render::Shader::Create(l.at(0), std::filesystem::path(l.at(1)), std::filesystem::path(l.at(2)));
		});
	m_MaterialRegistry = Spirit::AssetRegistry<Spirit::Render::Material>([](std::vector<std::string> l) {
		return std::make_shared<Spirit::Render::Material>();//TODO loading
		});
}

void Spirit::AssetLibrary::Update()
{
	m_MeshRegistry.Update();
	m_ShaderRegistry.Update();
	m_MaterialRegistry.Update();
}

Spirit::AssetRegistry<Spirit::Render::Mesh>& Spirit::AssetLibrary::GetMeshRegistry()
{
	return m_MeshRegistry;
}

Spirit::AssetRegistry<Spirit::Render::Shader>& Spirit::AssetLibrary::GetShaderRegistry()
{
	return m_ShaderRegistry;
}

Spirit::AssetRegistry<Spirit::Render::Material>& Spirit::AssetLibrary::GetMaterialRegistry()
{
	return m_MaterialRegistry;
}
