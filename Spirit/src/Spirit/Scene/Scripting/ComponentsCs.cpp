#include "sppch.h"
#include "ComponentsCs.h"

#include "ScriptController.h"
#include "Spirit/Scene/SceneManager.h"
#include "Spirit/Scene/Entity.h"
#include "Spirit/Scene/Components.h"
#include "Spirit/Application.h"
#include "Spirit/Core/AssetLibrary.h"

#pragma region TagComponent
static MonoString* Tag_GetTag_Native(unsigned int entityID) {
	return mono_string_new(mono_domain_get(), PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TagComponent>().Tag.c_str());
}

static void Tag_SetTag_Native(unsigned int entityID, MonoString* string) {
	PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TagComponent>().Tag = mono_string_to_utf8(string);
}
#pragma endregion



#pragma region TransformComponent 
static void Transform_GetPosition_Native(unsigned int entityID, glm::vec3* result)
{
	memcpy(result, &PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Position, sizeof(glm::vec3));
}

static void Transform_SetPosition_Native(unsigned int entityID, glm::vec3* result)
{
	PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Position = *result;
}


static void Transform_GetRotation_Native(unsigned int entityID, glm::vec3* result)
{
	memcpy(result, &PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Rotation, sizeof(glm::vec3));
}

static void Transform_SetRotation_Native(unsigned int entityID, glm::vec3* result)
{
	PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Rotation = *result;
}


static void Transform_GetScale_Native(unsigned int entityID, glm::vec3* result)
{
	memcpy(result, &PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Scale, sizeof(glm::vec3));
}

static void Transform_SetScale_Native(unsigned int entityID, glm::vec3* result)
{
	PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().Scale = *result;
}

static void Transform_GetForward_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 forward = PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetForward();

	memcpy(result, &forward, sizeof(glm::vec3));
}

static void Transform_GetBackward_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 backward = PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetBackward();

	memcpy(result, &backward, sizeof(glm::vec3));
}

static void Transform_GetLeft_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 left = PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetLeft();

	memcpy(result, &left, sizeof(glm::vec3));
}

static void Transform_GetRight_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 right = PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetRight();

	memcpy(result, &right, sizeof(glm::vec3));
}

static void Transform_GetUp_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 up = PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetUp();

	memcpy(result, &up, sizeof(glm::vec3));
}

static void Transform_GetDown_Native(unsigned int entityID, glm::vec3* result)
{
	glm::vec3 down = PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::TransformComponent>().GetDown();

	memcpy(result, &down, sizeof(glm::vec3));
}
#pragma endregion
#pragma region CameraComponent

#pragma endregion
#pragma region MeshRendererComponent
static MonoString* MeshRenderer_GetPath_Native(unsigned int entityID) {
	return mono_string_new(mono_domain_get(), PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::MeshRendererComponent>().Path.string().c_str());
}
static void MeshRenderer_SetPath_Native(unsigned int entityID, MonoString* string) {
	PROJECT->GetActiveScene()->GetEntityByIndex((entt::entity)entityID).GetComponent<Spirit::MeshRendererComponent>().Path = mono_string_to_utf8(string);
}
#pragma endregion

#pragma region MaterialRendererComponent
#pragma region Asset
static void AssetMaterial_GetAlbedo_Native(MonoString* path, glm::vec3* result) {
	glm::vec3 albedo = Spirit::AssetLibrary::GetMaterialRegistry().GetMember({ mono_string_to_utf8(path) })->Albedo;
	memcpy(result, &albedo, sizeof(glm::vec3));
}
static void AssetMaterial_SetAlbedo_Native(MonoString* path, glm::vec3* result) {
	//TODO MaterialSerializer
}

static void AssetMaterial_GetNormal_Native(MonoString* path, glm::vec3* result) {
	glm::vec3 normal = Spirit::AssetLibrary::GetMaterialRegistry().GetMember({ mono_string_to_utf8(path) })->Normal;
	memcpy(result, &normal, sizeof(glm::vec3));
}
static void AssetMaterial_SetNormal_Native(MonoString* path, glm::vec3* result) {
	//TODO MaterialSerializer
}

static void AssetMaterial_GetRoughness_Native(MonoString* path, float* result) {
	float roughness = Spirit::AssetLibrary::GetMaterialRegistry().GetMember({ mono_string_to_utf8(path) })->Roughness;
	memcpy(result, &roughness, sizeof(glm::vec3));
}
static void AssetMaterial_SetRoughness_Native(MonoString* path, float result) {
	//TODO MaterialSerializer
}

static void AssetMaterial_GetMetallic_Native(MonoString* path, float* result) {
	float metallic = Spirit::AssetLibrary::GetMaterialRegistry().GetMember({ mono_string_to_utf8(path) })->Metallic;
	memcpy(result, &metallic, sizeof(glm::vec3));
}
static void AssetMaterial_SetMetallic_Native(MonoString* path, float result) {
	//TODO MaterialSerializer
}

static void AssetMaterial_GetAO_Native(MonoString* path, float* result) {
	float ao = Spirit::AssetLibrary::GetMaterialRegistry().GetMember({ mono_string_to_utf8(path) })->AO;
	memcpy(result, &ao, sizeof(glm::vec3));
}
static void AssetMaterial_SetAO_Native(MonoString* path, float result) {
	//TODO MaterialSerializer
}
#pragma endregion
#pragma region Component

#pragma endregion

#pragma endregion


void Spirit::Scripting::ComponentsCs::Bind()
{
#pragma region TagComponent
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Tag::GetTag_Native", Tag_GetTag_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Tag::SetTag_Native", Tag_SetTag_Native);
#pragma endregion

#pragma region TransformComponent
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetPosition_Native", Transform_GetPosition_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::SetPosition_Native", Transform_SetPosition_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetRotation_Native", Transform_GetRotation_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::SetRotation_Native", Transform_SetRotation_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetScale_Native", Transform_GetScale_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::SetScale_Native", Transform_SetScale_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetForward_Native", Transform_GetForward_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetBackward_Native", Transform_GetBackward_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetLeft_Native", Transform_GetLeft_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetRight_Native", Transform_GetRight_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetUp_Native", Transform_GetUp_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.Transform::GetDown_Native", Transform_GetDown_Native);
#pragma endregion
#pragma region CameraComponent
#pragma endregion
#pragma region MeshRendererComponent
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.MeshRenderer::GetPath_Native", MeshRenderer_GetPath_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.MeshRenderer::SetPath_Native", MeshRenderer_SetPath_Native);
#pragma endregion
#pragma region MaterialRendererComponent
#pragma region Asset
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.AssetMaterial::GetAlbedo_Native", AssetMaterial_GetAlbedo_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.AssetMaterial::SetAlbedo_Native", AssetMaterial_SetAlbedo_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.AssetMaterial::GetNormal_Native", AssetMaterial_GetNormal_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.AssetMaterial::SetNormal_Native", AssetMaterial_SetNormal_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.AssetMaterial::GetRoughness_Native", AssetMaterial_GetRoughness_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.AssetMaterial::SetRoughness_Native", AssetMaterial_SetRoughness_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.AssetMaterial::GetMetallic_Native", AssetMaterial_GetMetallic_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.AssetMaterial::SetMetallic_Native", AssetMaterial_SetMetallic_Native);

	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.AssetMaterial::GetAO_Native", AssetMaterial_GetAO_Native);
	Spirit::Scripting::ScriptController::DirectBindCallback("SpiritScript.AssetMaterial::SetAO_Native", AssetMaterial_SetAO_Native);
#pragma endregion
#pragma region Component

#pragma endregion

	
#pragma endregion


	

	
}
