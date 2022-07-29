
#include "sppch.h"
#include "Entity.h"
#include "Scripting/ScriptController.h"
#include "Scripting/ScriptClass.h"
#include "Scripting/ScriptProperty.h"

Spirit::Entity::Entity(entt::entity handle, Scene* scene)
	: m_EntityHandle(handle), m_Scene(scene)
{
}
