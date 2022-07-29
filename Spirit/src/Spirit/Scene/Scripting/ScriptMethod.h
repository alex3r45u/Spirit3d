#pragma once
#include <string>

#include "ScriptObject.h"

namespace Spirit::Scripting {
	class ScriptMethod {
	public:
		ScriptMethod() = default;
		ScriptMethod(MonoMethod* method) : m_Method(method) {}
		std::string GetName();
		void Invoke(ParameterList params = {}, ScriptObject* object = nullptr);
	private:
		MonoMethod* m_Method;
	};
}