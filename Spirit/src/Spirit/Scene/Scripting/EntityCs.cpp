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
#include "Spirit/Application.h"


#define COMPONENTTYPE_FROM_NAME(N, T) if(strcmp(c, ##N)) {return T;}
#define ADD_COMPONENT(T, C) if(type == T) {entity.AddComponent<C>(); return;}
#define REMOVE_COMPONENT(T, C) if(type == T) {entity.RemoveComponent<C>(); return;}
#define HAS_COMPONENT(T, C) if(type == T && entity.HasComponent<C>()) {h = true;}
#define GET_COMPONENT(T, O) if(type == T) {c = Spirit::Scripting::ScriptController::GetDomain().GetClass(##O).CreateInstance().GetObjectPointer();}

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
}

static ComponentType GetType(MonoObject* object) {
	ComponentType type = ComponentType::None;

	MonoClass* klass = mono_object_get_class(object);

	const char* c = mono_string_to_utf8((MonoString*)mono_property_get_value(mono_class_get_property_from_name(klass, "Name"), object, nullptr, nullptr));

	COMPONENTTYPE_FROM_NAME("Transform", ComponentType::TransformComponent);
	COMPONENTTYPE_FROM_NAME("Tag", ComponentType::TagComponent);

	return ComponentType::Script;



}

static void AddComponent_Native(unsigned int entityID, MonoObject* object) {
	Spirit::Entity entity = PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID);
	ComponentType type = GetType(object);
	ADD_COMPONENT(ComponentType::TransformComponent, Spirit::TransformComponent);
	ADD_COMPONENT(ComponentType::TagComponent, Spirit::TagComponent);
	if (type == ComponentType::Script) {

	}
}

static void RemoveComponent_Native(unsigned int entityID, MonoObject* object) {
	Spirit::Entity entity = PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID);
	ComponentType type = GetType(object);
	REMOVE_COMPONENT(ComponentType::TransformComponent, Spirit::TransformComponent);
	REMOVE_COMPONENT(ComponentType::TagComponent, Spirit::TagComponent);
	
	//delete script
	return;
}

static void HasComponent_Native(unsigned int entityID, MonoObject* object, bool* has) {
	bool h = PROJECT->GetActiveScene()->GetScriptingECS().HasComponent(entityID, GetName(object));
	ComponentType type = GetType(object);
	Spirit::Entity entity = PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID);
	HAS_COMPONENT(ComponentType::TransformComponent, Spirit::TransformComponent);
	HAS_COMPONENT(ComponentType::TagComponent, Spirit::TagComponent);
	memcpy(has, &h, sizeof(bool));
	//has = &component;
}

static void GetComponent_Native(unsigned int entityID, MonoObject* object, MonoObject** component) {
	MonoObject* c;
	if (PROJECT->GetActiveScene()->GetScriptingECS().HasComponent(entityID, GetName(object))) {
		c = PROJECT->GetActiveScene()->GetScriptingECS().GetComponent(entityID, GetName(object))->GetObjectPointer();
	}
	else {
		ComponentType type = GetType(object);
		GET_COMPONENT(ComponentType::TransformComponent, "SpiritScript.Transform");
		GET_COMPONENT(ComponentType::TagComponent, "SpiritScript.Tag");
	}
	memcpy(component, &c, sizeof(MonoObject*));
}

static void NewEntity_Native(MonoObject* entity) {

}

static void GetEntity_Native(unsigned int entityID, MonoObject** entity) {
	MonoObject* e = PROJECT->GetActiveScene()->GetScriptingECS().GetEntity(entityID)->GetObjectPointer();
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
