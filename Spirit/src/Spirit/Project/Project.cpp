#include "sppch.h"
#include "Project.h"

Spirit::Project::Project(const Spirit::ProjectSettings& settings)
	: m_ProjectSettings(settings)
{

}

void Spirit::Project::SetSettings(const ProjectSettings& settings)
{
	m_ProjectSettings = settings;
}

Spirit::ProjectSettings& Spirit::Project::GetSettings()
{
	return m_ProjectSettings;
}
