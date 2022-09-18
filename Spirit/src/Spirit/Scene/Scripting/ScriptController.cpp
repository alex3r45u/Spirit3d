#include "sppch.h"
#include "ScriptController.h"


std::unique_ptr<Spirit::Scripting::ScriptDomain> Spirit::Scripting::ScriptController::m_Domain = nullptr;

void Spirit::Scripting::ScriptController::Init(const char* filename)
{
	assembly_name = filename;
	m_Domain = std::make_unique<ScriptDomain>(filename);
}

Spirit::Scripting::ScriptDomain& Spirit::Scripting::ScriptController::GetDomain()
{
	return *m_Domain;
}