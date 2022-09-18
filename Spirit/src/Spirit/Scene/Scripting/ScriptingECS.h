
#pragma once
#include <unordered_map>
#include "ScriptObject.h"
#include <functional>

namespace Spirit::Scripting {
	class ScriptingECS {
	public:
		ScriptingECS() = default;
		void AddEntity(unsigned int entityID, std::shared_ptr<ScriptObject> entity);
		std::shared_ptr<ScriptObject> GetEntity(unsigned int entityID);
		bool HasEntity(unsigned int entityID);
		void RemoveEntity(unsigned int entityID);



		void AddComponent(unsigned int entityID, std::shared_ptr<ScriptObject> component);
		std::shared_ptr<ScriptObject> GetComponent(unsigned int entityID, std::string componentName);
		std::list<std::shared_ptr<ScriptObject>>& GetAllScripts(unsigned int entityID);
		bool HasComponent(unsigned int entityID, std::string componentName);
		bool HasComponent(unsigned int entityID, std::shared_ptr<ScriptObject> component);
		void RemoveComponent(unsigned int entityID, std::string componentName);

		void UpdateScriptingECS();


		void DrawComponents(unsigned int entityID, std::function<void(std::shared_ptr<ScriptObject>)> drawFunction);
	private:
		std::shared_ptr<ScriptObject> GetComponentOutOfName(unsigned int entityID, std::string name);
	private:




		std::unordered_map<unsigned int, std::shared_ptr<ScriptObject>> m_Entities;
		std::unordered_map<unsigned int, std::list<std::shared_ptr<ScriptObject>>> m_Components;
	};
}
