#include "sppch.h"
#include "EntityCs.h"

#include "Spirit/Scene/Entity.h"
#include "Spirit/Scene/SceneManager.h"
#include "Spirit/Scene/Components.h"
#include <mono/jit/jit.h>

#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>
#include <mono/utils/mono-publib.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>
#include "ScriptController.h"
#include "ScriptProperty.h"

enum class ComponentType {
	None = 0,
	TagComponent,
	TransformComponent,
	Script,
};

static std::string GetName(MonoObject* object) {

	MonoClass* klass = mono_object_get_class(object);

	std::string build = mono_string_to_utf8((MonoString*)mono_property_get_value(mono_class_get_property_from_name(klass, "Namespace"), object, nullptr, nullptr));
	build.append(".");
	build.append(mono_string_to_utf8((MonoString*)mono_property_get_value(mono_class_get_property_from_name(klass, "Name"), object, nullptr, nullptr)));
	return build;
	//return Spirit::Scripting::ScriptController::GetDomain().GetObjectOutMonoObject(object).GetTypeName();
}

static ComponentType GetType(MonoObject* object) {
	ComponentType type = ComponentType::None;

	const char* c = GetName(object).c_str();

	if (std::strcmp(c, "Transform")) {
		type = ComponentType::TransformComponent;
	}
	else if (std::strcmp(c, "Tag")) {
		type = ComponentType::TagComponent;
	}

	else {
		type = ComponentType::Script;
	}

	return type;
}

static void AddComponent_Native(unsigned int entityID, MonoObject* object) {
	Spirit::Entity entity = Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID);

	switch (GetType(object)) {
	case ComponentType::TransformComponent:
		entity.AddComponent<Spirit::TransformComponent>();
		break;
	case ComponentType::TagComponent:
		entity.AddComponent<Spirit::TagComponent>();
		break;
	case ComponentType::Script:
		//entity.AddScript(Spirit::Scripting::ScriptController::GetDomain().GetObjectOutMonoObject(object));
		break;
		
	}
}

static void RemoveComponent_Native(unsigned int entityID, MonoObject* object) {
	Spirit::Entity entity = Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID);

	switch (GetType(object)) {
	case ComponentType::TransformComponent:
		entity.RemoveComponent<Spirit::TransformComponent>();
		break;
	case ComponentType::TagComponent:
		entity.RemoveComponent<Spirit::TagComponent>();
		break;
	case ComponentType::Script:
		//entity.RemoveScript(GetName(object));
		break;

	}
}

static void HasComponent_Native(unsigned int entityID, MonoObject* object, bool* has) {
	bool h = Spirit::SceneManager::GetActiveScene()->GetScriptingECS().HasComponent(entityID, GetName(object));
	memcpy(has, &h, sizeof(bool));
	//has = &component;
}

static void GetComponent_Native(unsigned int entityID, MonoObject* object, MonoObject** component) {
	MonoObject* c = Spirit::SceneManager::GetActiveScene()->GetScriptingECS().GetComponent(entityID, GetName(object))->GetObjectPointer();
	memcpy(component, &c, sizeof(MonoObject*));
}

static void NewEntity_Native(MonoObject* entity) {

}

static void GetEntity_Native(unsigned int entityID, MonoObject** entity) {
	MonoObject* e = Spirit::SceneManager::GetActiveScene()->GetScriptingECS().GetEntity(entityID)->GetObjectPointer();
	memcpy(entity,&e, sizeof(MonoObject*));
}

void Spirit::Scripting::EntityCs::Bind()
{
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Entity::AddComponent_Native", AddComponent_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Entity::RemoveComponent_Native", RemoveComponent_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Entity::HasComponent_Native", HasComponent_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Entity::GetComponent_Native", GetComponent_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Entity::NewEntity_Native", NewEntity_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Entity::GetEntity_Native", GetEntity_Native);
}
