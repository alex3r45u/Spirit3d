#pragma once
#include "AssetRegistry.h"
#include "Spirit/Render/Mesh.h"
#include "Spirit/Render/Material.h"
#include "Spirit/Render/Shader.h"

namespace Spirit {
	class AssetLibrary {
	public:
		static void Init();
		static void Update();
		static AssetRegistry<Spirit::Render::Mesh>& GetMeshRegistry();
		static AssetRegistry<Spirit::Render::Shader>& GetShaderRegistry();
		static AssetRegistry<Spirit::Render::Material>& GetMaterialRegistry();
	private:
		static AssetRegistry<Render::Mesh> m_MeshRegistry;
		static AssetRegistry<Render::Shader> m_ShaderRegistry;
		static AssetRegistry<Render::Material> m_MaterialRegistry;
	};
}