#include "sppch.h"
#include "Project.h"
#include "Spirit/Scene/SceneSerializer.h"

Spirit::Project::Project()
{
	m_ProjectSettings = ProjectSettings();
}

Spirit::Project::Project(const Spirit::ProjectSettings& settings)
	: m_ProjectSettings(settings)
{

}

void Spirit::Project::SetSettings(const ProjectSettings& settings)
{
	m_ProjectSettings = settings;
}

const Spirit::ProjectSettings& Spirit::Project::GetSettings()
{
	return m_ProjectSettings;
}

void Spirit::Project::SetScene(const std::shared_ptr<Scene>& scene)
{
	m_ActiveScene = scene;
}

void Spirit::Project::SetLoadScene(const std::filesystem::path& path)
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>(path);
	SceneSerializer serializer(scene);
	serializer.Deserialize(path);
	SetScene(scene);
}

void Spirit::Project::SaveActiveScene(const std::filesystem::path& path)
{
	SceneSerializer serializer(m_ActiveScene);
	serializer.Serialize(path);
}

std::shared_ptr<Spirit::Scene> Spirit::Project::GetActiveScene()
{
	return m_ActiveScene;
}
