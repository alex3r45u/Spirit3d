#pragma once
#include <unordered_map>
#include "ScriptClass.h"

namespace Spirit {
	class ProjectSettings;
}

namespace Spirit::Scripting {
	class ScriptDomain {
	public:
		ScriptDomain() = default;
		ScriptDomain(std::string filename, std::string filenameCore, const Spirit::ProjectSettings& settings);
		~ScriptDomain();
		void Reload(std::string filename, std::string filenameCore, const Spirit::ProjectSettings& settings);
		void Unload();
		void Load(std::string filename, std::string filenameCore, const Spirit::ProjectSettings& settings);
		ScriptClass& GetClass(const std::string& name);
		ScriptObject& GetObjectOutMonoObject(MonoObject* object);
		bool ClassExist(const std::string& name);
	private:
		void InitAssemblies(std::string filename, std::string filenameCore, const Spirit::ProjectSettings& settings);
	private:
		MonoDomain* m_Domain = nullptr;
		MonoDomain* m_Root = nullptr;
		MonoAssembly* m_Assembly = nullptr;
		MonoImage* m_Image = nullptr;
		MonoAssembly* m_CoreAssembly = nullptr;
		MonoImage* m_CoreImage = nullptr;
		std::unordered_map<std::string, std::shared_ptr<ScriptClass>> m_Classes;
	};
}