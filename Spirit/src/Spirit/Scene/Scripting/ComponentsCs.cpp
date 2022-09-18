#include "sppch.h"
#include "ComponentsCs.h"

#include "ScriptController.h"
#include "Spirit/Scene/SceneManager.h"
#include "Spirit/Scene/Entity.h"
#include "Spirit/Scene/Components.h"

#pragma region TagComponent
static MonoString* GetTag_Native(unsigned int entityID) {
	return mono_string_new(mono_domain_get(), Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TagComponent>().Tag.c_str());
}

static void SetTag_Native(unsigned int entityID, MonoString* string) {
	Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TagComponent>().Tag = mono_string_to_utf8(string);
}
#pragma endregion



#pragma region TransformComponent 
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

static void GetForward_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 forward = Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetForward();

	memcpy(result, &forward, sizeof(glm::vec3));
}

static void GetBackward_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 backward = Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetBackward();

	memcpy(result, &backward, sizeof(glm::vec3));
}

static void GetLeft_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 left = Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetLeft();

	memcpy(result, &left, sizeof(glm::vec3));
}

static void GetRight_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 right = Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetRight();

	memcpy(result, &right, sizeof(glm::vec3));
}

static void GetUp_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 up = Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetUp();

	memcpy(result, &up, sizeof(glm::vec3));
}

static void GetDown_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 down = Spirit::SceneManager::GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetDown();

	memcpy(result, &down, sizeof(glm::vec3));
}
#pragma endregion



void Spirit::Scripting::ComponentsCs::Bind()
{
#pragma region TagComponent
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Tag::GetTag_Native", GetTag_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Tag::SetTag_Native", SetTag_Native);
#pragma endregion

#pragma region TransformComponent
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetPosition_Native", GetPosition_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::SetPosition_Native", SetPosition_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetRotation_Native", GetRotation_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::SetRotation_Native", SetRotation_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetScale_Native", GetScale_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::SetScale_Native", SetScale_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetForward_Native", GetForward_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetBackward_Native", GetBackward_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetLeft_Native", GetLeft_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetRight_Native", GetRight_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetUp_Native", GetUp_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetDown_Native", GetDown_Native);
#pragma endregion

	

	
}
