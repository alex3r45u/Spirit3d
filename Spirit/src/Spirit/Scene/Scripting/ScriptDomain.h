#pragma once
#include <unordered_map>
#include "ScriptClass.h"


namespace Spirit::Scripting {
	class ScriptDomain {
	public:
		ScriptDomain() = default;
		ScriptDomain(const char* filename, const char* filenameCore);
		~ScriptDomain();

		ScriptClass& GetClass(const std::string& name);
		ScriptObject& GetObjectOutMonoObject(MonoObject* object);
		bool ClassExist(const std::string& name);

	private:
		MonoDomain* m_Domain = nullptr;
		MonoAssembly* m_Assembly = nullptr;
		MonoImage* m_Image = nullptr;
		MonoAssembly* m_CoreAssembly = nullptr;
		MonoImage* m_CoreImage = nullptr;
		std::unordered_map<std::string, std::shared_ptr<ScriptClass>> m_Classes;
	};
}