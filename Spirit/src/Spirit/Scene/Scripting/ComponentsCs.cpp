#include "sppch.h"
#include "ComponentsCs.h"

#include "ScriptController.h"
#include "Spirit/Scene/SceneManager.h"
#include "Spirit/Scene/Entity.h"
#include "Spirit/Scene/Components.h"

static MonoString* GetTag_Native(unsigned int entityID) {
	return mono_string_new(mono_domain_get(), Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TagComponent>().Tag.c_str());
}

static void SetTag_Native(unsigned int entityID, MonoString* string) {
	Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TagComponent>().Tag = mono_string_to_utf8(string);
}

static void GetPosition_Native(unsigned int entityID, glm::vec3* result)
{
	memcpy(result, &Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Position, sizeof(glm::vec3));
}

static void SetPosition_Native(unsigned int entityID, glm::vec3* result)
{
	Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Position = *result;
}


static void GetRotation_Native(unsigned int entityID, glm::vec3* result)
{
	memcpy(result, &Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Rotation, sizeof(glm::vec3));
}

static void SetRotation_Native(unsigned int entityID, glm::vec3* result)
{
	Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Rotation = *result;
}


static void GetScale_Native(unsigned int entityID, glm::vec3* result)
{
	memcpy(result, &Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Scale, sizeof(glm::vec3));
}

static void SetScale_Native(unsigned int entityID, glm::vec3* result)
{
	Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Scale = *result;
}

void Spirit::Scripting::ComponentsCs::Bind()
{
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Tag::GetTag_Native", GetTag_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Tag::SetTag_Native", SetTag_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetPosition_Native", GetPosition_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::SetPosition_Native", SetPosition_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetRotation_Native", GetRotation_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::SetRotation_Native", SetRotation_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetScale_Native", GetScale_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::SetScale_Native", SetScale_Native);
}
