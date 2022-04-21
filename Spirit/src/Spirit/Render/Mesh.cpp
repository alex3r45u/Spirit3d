#include "sppch.h"
#include "Mesh.h"






void Spirit::Render::Mesh::Render(std::shared_ptr<Shader> shader)
{
	for (auto va : m_VertexArray) {
		glm::mat4 pos = glm::mat4(1.0f);
		Spirit::Render::Renderer::Submit(va, shader, pos);
	}
	
}

void Spirit::Render::Mesh::LoadModel(const std::string& path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
	processNode(scene->mRootNode, scene);
}

void Spirit::Render::Mesh::processNode(aiNode* node, const aiScene* scene)
{
	// process all meshes
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_VertexArray.push_back(processMesh(mesh, scene));
	}

	// process all child nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

std::shared_ptr<Spirit::Render::VertexArray> Spirit::Render::Mesh::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::shared_ptr<VertexArray> vertexArray;
	vertexArray.reset(Spirit::Render::VertexArray::Create());


	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	// vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {


		// position
		glm::vec3 pos = glm::vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		vertices.push_back(pos.x);
		vertices.push_back(pos.y);
		vertices.push_back(pos.z);

		glm::vec3 normal = glm::vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		);

		vertices.push_back(normal.x);
		vertices.push_back(normal.y);
		vertices.push_back(normal.z);

		// textures
		if (mesh->mTextureCoords[0]) {
			glm::vec2 texCoord = glm::vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
			vertices.push_back(texCoord.x);
			vertices.push_back(texCoord.y);
		}
		else {
			vertices.push_back(0);
			vertices.push_back(0);
		}
		
	}
	std::shared_ptr<Spirit::Render::VertexBuffer> vertexBuffer;
	vertexBuffer = Spirit::Render::VertexBuffer::Create(vertices.data(), vertices.size()*sizeof(float));
	Spirit::Render::BufferLayout layout = {
		{ Spirit::Render::ShaderDataType::Float3, "a_Position" },
		{ Spirit::Render::ShaderDataType::Float3, "a_Normal" },
		{ Spirit::Render::ShaderDataType::Float2, "a_Tex" },
	};
	vertexBuffer->SetLayout(layout);
	vertexArray->AddVertexBuffer(vertexBuffer);

	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}

	std::shared_ptr<Spirit::Render::IndexBuffer> indexBuffer;
	indexBuffer = Spirit::Render::IndexBuffer::Create(indices.data(), indices.size());
	vertexArray->SetIndexBuffer(indexBuffer);



	return vertexArray;
}
