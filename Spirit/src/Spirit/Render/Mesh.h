#pragma once 
#include "VertexArray.h"
#include "Material.h"


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <filesystem>

namespace Spirit::Render {

	class Mesh {
	public:
		Mesh() {}
		Mesh(const std::string& meshPath) { LoadModel(meshPath); }
		std::filesystem::path GetPath() { return m_Path; }
		const std::vector<std::shared_ptr<VertexArray>>& GetVertexArray() const { return m_VertexArray; }
	private:
		std::vector<std::shared_ptr<VertexArray>> m_VertexArray;

		void LoadModel(const std::string& path);
		void processNode(aiNode* node, const aiScene* scene);
		std::shared_ptr<Spirit::Render::VertexArray> processMesh(aiMesh* mesh, const aiScene* scene);

		std::filesystem::path m_Path;
		
		
	};

	
}