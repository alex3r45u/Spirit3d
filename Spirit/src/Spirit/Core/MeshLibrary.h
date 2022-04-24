#pragma once
#include <memory>
#include "Spirit/Render/Mesh.h"

namespace Spirit {
	class MeshLibrary {
	public:
		MeshLibrary() {}
		void Add(const std::string& name, const std::shared_ptr<Render::Mesh>& mesh);
		void Load(const std::string& name, const std::string& path);
		const std::shared_ptr<Render::Mesh> Get(const std::string& name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<Render::Mesh>> m_Meshes;
	};
}