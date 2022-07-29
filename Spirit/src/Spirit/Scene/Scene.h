#pragma once
#include "entt.hpp"
#include "Spirit/Core/Timestep.h"
#include <string>
#include "Scripting/ScriptingECS.h"

namespace Spirit {
	class Entity;

	class Scene {
	public:
		Scene();
		Scene(const std::string& name);
		~Scene();

		Entity CreateEntity(const std::string& name);
		void RemoveEntity(Entity& entity);

		void OnUpdate(TimeStep ts);
		void OnReseize(unsigned int width, unsigned int height);
		Entity GetEntityByIndex(entt::entity handle);
		std::string GetName() { return m_Name; }
		void SetName(const std::string& name);

		Scripting::ScriptingECS& GetScriptingECS() { return m_ScriptingECS; }

	private:
		entt::registry m_Registry;
		std::string m_Name;
		Scripting::ScriptingECS m_ScriptingECS;
		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class PropertiesPanel;
	};
}