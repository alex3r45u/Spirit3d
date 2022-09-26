#pragma once
#include <list>
#include <filesystem>
#include "Spirit/Scene/SceneManager.h"

namespace Spirit {
	struct ProjectSettings {
		std::string StartScene;
		std::filesystem::path Path;
		std::filesystem::path AssetPath;
		std::filesystem::path RessourcePath;
		std::filesystem::path ScriptSoulutionPath;
		//TODO
	};
	class Project {
	public:
		Project() = default;
		Project(const ProjectSettings& settings);
		void SetSettings(const ProjectSettings& settings);
		ProjectSettings& GetSettings();
	private:
		ProjectSettings m_ProjectSettings;
		
	};
}