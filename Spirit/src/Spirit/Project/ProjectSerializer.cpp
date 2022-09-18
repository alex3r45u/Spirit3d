#include "sppch.h"
#include "ProjectSerializer.h"
#include <yaml-cpp/yaml.h>
#define yaml(y) << YAML::##y
#define value << YAML::Value <<
#define key << YAML::Key <<

Spirit::ProjectSerializer::ProjectSerializer(const std::shared_ptr<Spirit::Project>& project)
	: m_Project(project)
{
}

void Spirit::ProjectSerializer::Serialize(const std::filesystem::path& filepath)
{
	YAML::Emitter out;

	out yaml(BeginMap);
	out key "Name" value m_Project->GetSettings().Path.filename().string();
	out key "Settings" yaml(BeginMap);
	//Settings
	out key "StartScene" value m_Project->GetSettings().StartScene;
	out key "Path" value m_Project->GetSettings().Path.string();
	out key "AssetPath" value m_Project->GetSettings().AssetPath.string();
	out key "ScriptSolutionPath" value m_Project->GetSettings().ScriptSoulutionPath.string();
	out yaml(EndMap);
	out yaml(EndMap);
}

bool Spirit::ProjectSerializer::Deserialize(const std::filesystem::path& filepath)
{
	return false;
}
