#pragma once
#include <memory>
#include "Spirit/Render/Mesh.h"

namespace Spirit {
	class MeshLibrary {
	public:
		MeshLibrary() {}
		void Add(const std::string& name, const std::shared_ptr<Render::Mesh>& mesh);
		std::shared_ptr<Render::Mesh> Get(const std::string& path);
		bool Exists(const std::string& path) const;
	private:
		void Load(const std::string& name, const std::string& path);
		std::unordered_map<std::string, std::shared_ptr<Render::Mesh>> m_Meshes;
	};
}