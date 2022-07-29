#pragma once
#include <string>
#include <memory>
#include "ScriptDomain.h"

static const char* assembly_name;

namespace Spirit::Scripting {
	class ScriptController {
	public:
		static void Init(const char* filename);
		static ScriptDomain& GetDomain();

		template<typename Func>
		static void DirectBindCallback(const std::string& fullName, Func func) {
			mono_add_internal_call(fullName.c_str(), (const void*)func);
		}
	private:
		static std::unique_ptr<ScriptDomain> m_Domain;
	};
}