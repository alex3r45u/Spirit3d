
#include "sppch.h"
#include "Entity.h"


Spirit::Entity::Entity(entt::entity handle, Scene* scene)
	: m_EntityHandle(handle), m_Scene(scene)
{
}