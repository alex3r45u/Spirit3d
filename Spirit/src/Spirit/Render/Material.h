#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
#include "Shader.h"
#include <filesystem>

namespace Spirit::Render {


	struct Material {
		Material() = default;
		Material(const Material&) = default;
		glm::vec3 Albedo;
		glm::vec3 Normal;
		float Roughness;
		float Metallic;
		float AO;
		
		std::shared_ptr<Texture> AlbedoMap;
		std::shared_ptr<Texture> NormalMap;
		std::shared_ptr<Texture> RoughnessMap;
		std::shared_ptr<Texture> MetallicMap;
		std::shared_ptr<Texture> AOMap;
	};

	struct AssetMaterial : public Material {
		std::filesystem::path Path;
		AssetMaterial() = default;
		AssetMaterial(const AssetMaterial&) = default;
	};
}