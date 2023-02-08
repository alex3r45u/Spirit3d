#include "sppch.h"
#include "ScriptController.h"
#include "Spirit/Project/Project.h"

std::unique_ptr<Spirit::Scripting::ScriptDomain> Spirit::Scripting::ScriptController::m_Domain = nullptr;
std::string Spirit::Scripting::ScriptController::m_Filename;
std::string Spirit::Scripting::ScriptController::m_FilenameCore;

void Spirit::Scripting::ScriptController::Init(const std::string& filename, const std::string& filenameCore, Spirit::ProjectSettings settings)
{
	//assembly_name = filename;
	m_Filename = filename;
	m_FilenameCore = filenameCore;
	m_Domain = std::make_unique<ScriptDomain>(filename, filenameCore, settings);
}

void Spirit::Scripting::ScriptController::Reload(Spirit::ProjectSettings settings)
{
	m_Domain->Reload(m_Filename.c_str(), m_FilenameCore.c_str(), settings);
}

void Spirit::Scripting::ScriptController::Load(Spirit::ProjectSettings settings)
{
	m_Domain->Load(m_Filename.c_str(), m_FilenameCore.c_str(), settings);
}

void Spirit::Scripting::ScriptController::Unload()
{
	m_Domain->Unload();
}

Spirit::Scripting::ScriptDomain& Spirit::Scripting::ScriptController::GetDomain()
{
	return *m_Domain;
}
