#pragma once 
#include "VertexArray.h"
#include "Material.h"

#include "Renderer.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace Spirit::Render {

	class Mesh {
	public:
		Mesh() {}
		Mesh(const std::string& meshPath) { LoadModel(meshPath); }
	
		void Render(std::shared_ptr<Shader> shader);
		const std::vector<std::shared_ptr<VertexArray>>& GetVertexArray() const { return m_VertexArray; }
		const std::vector<std::shared_ptr<Material>>& GetMaterial() const { return m_Material; }
	private:
		std::vector<std::shared_ptr<VertexArray>> m_VertexArray;
		std::vector<std::shared_ptr<Material>> m_Material;

		void LoadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		std::shared_ptr<Spirit::Render::VertexArray> processMesh(aiMesh* mesh, const aiScene* scene);
		
		
	};

	
}