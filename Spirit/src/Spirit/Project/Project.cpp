#include "sppch.h"
#include "Project.h"

Spirit::Project::Project(const std::filesystem::path path, const std::filesystem::path& assetPath, const std::filesystem::path& scriptSoulutionPath)
{
	m_ProjectSettings.Path = path;
	m_ProjectSettings.AssetPath = assetPath;
	m_ProjectSettings.ScriptSoulutionPath = scriptSoulutionPath;
}

void Spirit::Project::SetSettings(const ProjectSettings& settings)
{
	m_ProjectSettings = settings;
}

Spirit::ProjectSettings& Spirit::Project::GetSettings()
{
	return m_ProjectSettings;
}
