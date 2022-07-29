#pragma once
#include <unordered_map>
#include <memory>
#include "ScriptMethod.h"


namespace Spirit::Scripting {
	class ScriptClass {
	public:
		ScriptClass(MonoClass* _class, MonoDomain* domain);

		ScriptObject CreateInstance();

		void Invoke(const std::string& method, ParameterList params = {});
		std::string GetName() const;

		std::vector<std::string> GetFieldNames() const;
		std::vector<std::string> GetMethodNames() const;
		std::vector<std::string> GetPropertyNames() const;
		std::vector<std::string> GetEventNames() const;

		std::unordered_map<std::string, std::shared_ptr<ScriptMethod>> GetAllMethods() const;

	private:
		MonoClass* m_Class;
		MonoDomain* m_Domain;
		std::unordered_map<std::string, std::shared_ptr<ScriptMethod>> m_Methods;
	};
}