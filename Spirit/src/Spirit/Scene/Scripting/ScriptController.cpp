#include "sppch.h"
#include "ScriptController.h"


std::unique_ptr<Spirit::Scripting::ScriptDomain> Spirit::Scripting::ScriptController::m_Domain = nullptr;
std::string Spirit::Scripting::ScriptController::m_Filename;
std::string Spirit::Scripting::ScriptController::m_FilenameCore;

void Spirit::Scripting::ScriptController::Init(const std::string& filename, const std::string& filenameCore)
{
	//assembly_name = filename;
	m_Filename = filename;
	m_FilenameCore = filenameCore;
	m_Domain = std::make_unique<ScriptDomain>(filename, filenameCore);
}

void Spirit::Scripting::ScriptController::Reload()
{
	m_Domain->Reload(m_Filename.c_str(), m_FilenameCore.c_str());
}

void Spirit::Scripting::ScriptController::Load()
{
	m_Domain->Load(m_Filename.c_str(), m_FilenameCore.c_str());
}

void Spirit::Scripting::ScriptController::Unload()
{
	m_Domain->Unload();
}

Spirit::Scripting::ScriptDomain& Spirit::Scripting::ScriptController::GetDomain()
{
	return *m_Domain;
}
