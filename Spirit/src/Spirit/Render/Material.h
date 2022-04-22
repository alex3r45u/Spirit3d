#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
#include "Shader.h"

namespace Spirit::Render {
	struct Material {
		virtual const glm::vec3& GetAmbient() = 0;
		virtual const glm::vec3& GetDeffuse() = 0;
		virtual const glm::vec3& GetSpecular() = 0;

		virtual const std::shared_ptr<Texture2d> GetAmbientTexture() = 0;
		virtual const std::shared_ptr<Texture2d> GetDeffuseTexture() = 0;
		virtual const std::shared_ptr<Texture2d> GetSpecularTexture() = 0;

		void SetUniforms(const std::shared_ptr<Shader>& shader);
	};

	struct DefinedMaterials {
		static std::shared_ptr<Material> standard;
	};

	struct GeneratedMaterial : public Material {
		GeneratedMaterial() {}
		GeneratedMaterial(const glm::vec3& ambient) : ambient(ambient) {}
		GeneratedMaterial(const glm::vec3& ambient, const glm::vec3& deffuse, const glm::vec3& specular) : ambient(ambient), deffuse(deffuse), specular(specular) {}
		virtual const glm::vec3& GetAmbient() override { return ambient; }
		virtual const glm::vec3& GetDeffuse() override { return deffuse; }
		virtual const glm::vec3& GetSpecular() override { return specular; }

		virtual const std::shared_ptr<Texture2d> GetAmbientTexture() override;
		virtual const std::shared_ptr<Texture2d> GetDeffuseTexture() override;
		virtual const std::shared_ptr<Texture2d> GetSpecularTexture() override;


		glm::vec3 ambient;
		bool hasAmbientTexture = false;
		const std::shared_ptr<Texture2d> ambientTexture;

		glm::vec3 deffuse;
		bool hasDeffuseTexture = false;
		const std::shared_ptr<Texture2d> deffuseTexture;

		glm::vec3 specular;
		bool hasSpecularTexture = false;
		const std::shared_ptr<Texture2d> specularTexture;
	private:
		const std::shared_ptr<Texture2d> ambientRef;
		const std::shared_ptr<Texture2d> deffuseRef;
		const std::shared_ptr<Texture2d> specularRef;

	};

	struct UserMaterial : public Material {
		virtual const glm::vec3& GetAmbient() override { return ambient; }
		virtual const glm::vec3& GetDeffuse() override { return deffuse; }
		virtual const glm::vec3& GetSpecular() override { return specular; }

		virtual const std::shared_ptr<Texture2d> GetAmbientTexture() override;
		virtual const std::shared_ptr<Texture2d> GetDeffuseTexture() override;
		virtual const std::shared_ptr<Texture2d> GetSpecularTexture() override;


		glm::vec3 ambient;
		bool hasAmbientTexture;
		const std::string& ambientTexturePath;

		glm::vec3 deffuse;
		bool hasDeffuseTexture;
		const std::string& deffuseTexturePath;

		glm::vec3 specular;
		bool hasSpecularTexture;
		const std::string& specularTexturePath;

	};
}