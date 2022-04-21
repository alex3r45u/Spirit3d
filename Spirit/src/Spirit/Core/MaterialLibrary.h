#pragma once
#include <memory>
#include "Spirit/Render/Material.h"

namespace Spirit {
	class MaterialLibrary {
	public:
		MaterialLibrary() {}
		void Add(const std::string& name, const std::shared_ptr<Render::Material>& material);
		void Load(const std::string& name, const std::string& path);
		const std::shared_ptr<Render::Material> Get(const std::string& name);
		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<Render::Material>> m_Materials;
	};
}