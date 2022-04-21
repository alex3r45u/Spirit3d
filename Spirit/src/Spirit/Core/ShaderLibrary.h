#pragma once
#include "Spirit/Render/Shader.h"

namespace Spirit {
	class ShaderLibrary {
	public:
		ShaderLibrary() {}
		void Add(const std::string& name, const std::shared_ptr<Render::Shader>& shader);
		void Add(const std::shared_ptr<Render::Shader>& shader);
		std::shared_ptr<Render::Shader> Load(const std::string& name, const std::string& vertPath, const std::string& fragPath);

		std::shared_ptr<Render::Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, std::shared_ptr<Render::Shader>> m_Shaders;
	};
}