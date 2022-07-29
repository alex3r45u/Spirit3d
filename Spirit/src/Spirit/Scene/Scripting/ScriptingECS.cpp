#include "sppch.h"
#include "ScriptingECS.h"
#include "ScriptProperty.h"

#include "ScriptController.h"
#include "Spirit/Scene/SceneManager.h"


void Spirit::Scripting::ScriptingECS::AddEntity(unsigned int entityID, std::shared_ptr<ScriptObject> entity)
{
	if(!HasEntity(entityID))
		m_Entities[entityID] = entity;
}

std::shared_ptr<Spirit::Scripting::ScriptObject> Spirit::Scripting::ScriptingECS::GetEntity(unsigned int entityID)
{
	if (HasEntity(entityID))
		return m_Entities[entityID];
	return nullptr;
}

bool Spirit::Scripting::ScriptingECS::HasEntity(unsigned int entityID)
{
	return m_Entities.find(entityID) != m_Entities.end();
}

void Spirit::Scripting::ScriptingECS::RemoveEntity(unsigned int entityID)
{
	if (HasEntity(entityID))
		m_Entities.erase(entityID);
	if (m_Components.find(entityID) != m_Components.end())
		m_Components.erase(entityID);
}

void Spirit::Scripting::ScriptingECS::AddComponent(unsigned int entityID, std::shared_ptr<ScriptObject> component)
{
	if (!HasEntity(entityID)) {
		m_Entities[entityID] = std::make_shared<ScriptObject>(ScriptController::GetDomain().GetClass("SpiritScript.Entity").CreateInstance());
		m_Entities[entityID]->GetProperty("ID").Set(entityID);
		AddComponent(entityID,std::make_shared<ScriptObject>(ScriptController::GetDomain().GetClass("SpiritScript.Transform").CreateInstance()));
		AddComponent(entityID, std::make_shared<ScriptObject>(ScriptController::GetDomain().GetClass("SpiritScript.Tag").CreateInstance()));
	}
	component->GetProperty("entityID").Set(entityID);
	if (!HasComponent(entityID, component))
		m_Components[entityID].push_back(component);
		component->Invoke("Start");
}

std::shared_ptr<Spirit::Scripting::ScriptObject> Spirit::Scripting::ScriptingECS::GetComponent(unsigned int entityID, std::string componentName)
{
	auto c = GetComponentOutOfName(entityID, componentName);
	return c;
}

bool Spirit::Scripting::ScriptingECS::HasComponent(unsigned int entityID, std::string componentName)
{
	for (auto c : m_Components[entityID]) {
		if (c->GetTypeName() == componentName)
			return true;
	}
	return false;
}

bool Spirit::Scripting::ScriptingECS::HasComponent(unsigned int entityID, std::shared_ptr<ScriptObject> component)
{
	for (auto c : m_Components[entityID]) {
		if (c->GetObjectPointer() == component->GetObjectPointer())
			return true;
	}
	return false;
}

void Spirit::Scripting::ScriptingECS::RemoveComponent(unsigned int entityID, std::string componentName)
{
	for (auto c : m_Components[entityID]) {
		if (c->GetTypeName() == componentName)
			m_Components[entityID].remove(c);
	}
		
		
}

void Spirit::Scripting::ScriptingECS::UpdateScriptingECS()
{
	for (auto list : m_Components) {
		for (auto c : list.second) {
			c->Invoke("Update");
		}
	}
}

void Spirit::Scripting::ScriptingECS::DrawComponents(unsigned int entityID, std::function<void(std::shared_ptr<ScriptObject>)> drawFunction)
{
	for (auto c : m_Components[entityID]) {
		drawFunction(c);
	}
}

std::shared_ptr<Spirit::Scripting::ScriptObject> Spirit::Scripting::ScriptingECS::GetComponentOutOfName(unsigned int entityID, std::string name)
{
	for (auto c : m_Components[entityID]) {
		if (c->GetTypeName() == name)
			return c;
	}
	return nullptr;
}
