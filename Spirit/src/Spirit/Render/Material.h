#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
#include "Shader.h"
#include <filesystem>

namespace Spirit::Render {


	struct Material {
		Material() : Ambient(1.0f), Deffuse(.5f), Specular(.5f), Shininess(1.0f) {}
		Material(const glm::vec3& ambient, const glm::vec3& deffuse, const glm::vec3& specular, float shininess) : Ambient(ambient), Deffuse(deffuse), Specular(specular), Shininess(shininess) {}

		void SetUniforms(const std::shared_ptr<Shader>& shader);

		std::filesystem::path GetAmbientPath() { return m_AmbientTexturePath; }
		std::filesystem::path GetDeffusePath() { return m_DeffuseTexturePath; }
		std::filesystem::path GetSpecularPath() { return m_SpecularTexturePath; }

		void SetAmbientPath(std::filesystem::path& path) { m_AmbientTexturePath = path; }
		void SetDeffusePath(std::filesystem::path& path) { m_DeffuseTexturePath = path; }
		void SetSpecularPath(std::filesystem::path& path) { m_SpecularTexturePath = path; }

		glm::vec3 Ambient = glm::vec3(0.0f);
		bool HasAmbientTexture = false;
		glm::vec3 Deffuse;
		bool HasDeffuseTexture = false;
		glm::vec3 Specular;
		bool HasSpecularTexture = false;
		float Shininess;

	private:
		std::filesystem::path m_AmbientTexturePath;
		std::filesystem::path m_DeffuseTexturePath;
		std::filesystem::path m_SpecularTexturePath;

		std::shared_ptr<Texture> m_AmbientTexture;
		std::shared_ptr<Texture> m_DeffuseTexture;
		std::shared_ptr<Texture> m_SpecularTexture;
	};
}