#pragma once


#include <string>
#include <unordered_map>
#include <memory>


#include <mono/jit/jit.h>

#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>
#include <mono/utils/mono-publib.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>

#include "ParameterList.h"




namespace Spirit::Scripting {
	class ScriptMethod;
	class ScriptField;
	class ScriptProperty;
	

	class ScriptObject
	{
	public:
		ScriptObject() = default;
		ScriptObject(MonoObject* object,
			const std::unordered_map<std::string, std::shared_ptr<ScriptMethod>>& methods);

		void Invoke(const std::string& method, ParameterList params = {});

		MonoObject* GetObjectPointer() const;

		std::string GetTypeName() const;

		ScriptProperty& GetProperty(const std::string& name);
		ScriptField& GetField(const std::string& name);

	private:
		MonoObject* m_Object;
		std::unordered_map<std::string, std::shared_ptr<ScriptField>> m_Fields;
		std::unordered_map<std::string, std::shared_ptr<ScriptMethod>> m_Methods;
		std::unordered_map<std::string, std::shared_ptr<ScriptProperty>> m_Properties;
	};
}