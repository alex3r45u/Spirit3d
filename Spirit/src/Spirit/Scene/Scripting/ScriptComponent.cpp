#include "sppch.h"
#include "ScriptComponent.h"

Spirit::Scripting::ScriptComponent::ScriptComponent(ScriptObject& object)
	: m_ScriptObject(object)
{
}

bool Spirit::Scripting::ScriptComponent::GetDisplay()
{
	return m_Display;
}

void Spirit::Scripting::ScriptComponent::GetDisplay(bool value)
{
	m_Display = value;
}

Spirit::Scripting::ScriptObject& Spirit::Scripting::ScriptComponent::GetScriptObject()
{
	return m_ScriptObject;
}
