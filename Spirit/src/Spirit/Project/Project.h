#pragma once
#include <list>
#include "Spirit/Scene/SceneManager.h"

namespace Spirit {
	struct ProjectSettings {
		std::string StartScene;
		std::filesystem::path Path;
		std::filesystem::path AssetPath;
		std::filesystem::path ScriptSoulutionPath;
		//TODO
	};
	class Project {
	public:
		Project(const std::filesystem::path path, const std::filesystem::path& assetPath, const std::filesystem::path& scriptSoulutionPath);
		void SetSettings(const ProjectSettings& settings);
		ProjectSettings& GetSettings();
	private:
		ProjectSettings m_ProjectSettings;
		
	};
}