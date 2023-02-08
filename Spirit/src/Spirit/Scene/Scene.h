#pragma once
#include "entt.hpp"
#include "Spirit/Core/Timestep.h"
#include <string>
#include "Scripting/ScriptingECS.h"
#include <filesystem>


namespace Spirit {
	namespace Render {
		class EditorCamera;
	}
	class Entity;

	class Scene {
	public:
		Scene();
		Scene(const std::filesystem::path& path);
		Scene(const Scene&) = default;
		~Scene();

		Entity CreateEntity(const std::string& name);
		void RemoveEntity(Entity& entity);

		void Start();
		void Stop();

		void OnUpdate(TimeStep ts);
		void OnRunUpdate(TimeStep ts);
		void OnReseize(unsigned int width, unsigned int height);
		Entity GetEntityByIndex(entt::entity handle);
		std::filesystem::path GetPath() { return m_Path; }
		void SetPath(const std::filesystem::path& path);

		Scripting::ScriptingECS& GetScriptingECS() { return m_ScriptingECS; }

	private:
		entt::registry m_Registry;
		std::filesystem::path m_Path;
		Scripting::ScriptingECS m_ScriptingECS;
		std::shared_ptr<Spirit::Render::EditorCamera> m_EditorCamera;
		bool m_IsRunning;
		friend class Entity;
		friend class SceneHierarchyPanel;
		friend class PropertiesPanel;
		friend class SceneSerializer;
	};
}