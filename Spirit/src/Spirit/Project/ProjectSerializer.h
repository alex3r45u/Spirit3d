#pragma once
#include <filesystem>
#include "Project.h"

namespace Spirit {
	class ProjectSerializer {
	public:
		ProjectSerializer(const std::shared_ptr<Spirit::Project>& project);

		static std::shared_ptr<Project> CreateProject(const std::filesystem::path& filePath, const std::filesystem::path& ressourcePath);

		void Serialize(const std::filesystem::path& filepath);

		bool Deserialize(const std::filesystem::path& filepath);

	private:
		std::shared_ptr<Project> m_Project;
	};
}