#pragma once


#include <string>
#include <mono/jit/jit.h>

#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>
#include <mono/utils/mono-publib.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>

namespace Spirit::Scripting {
	class ScriptProperty {
	public:
		ScriptProperty(MonoObject* object, MonoProperty* _property);

		std::string GetName() const;

		bool HasSetProperty() const;
		bool HasGetProperty() const;

		template<typename T>
		T Get() const {
			MonoObject* result = mono_runtime_invoke(m_GetMethod, m_Object, nullptr, nullptr);

			return *(T*)mono_object_unbox(result);
		}

		template<typename T>
		void Set(T value) {
			if (m_SetMethod == nullptr)
				SP_CORE_ERROR("Set method doesn't exists");

			void* params[1];
			params[0] = &value;

			mono_property_set_value(m_Property, m_Object, params, nullptr);
		}
	private:
		MonoProperty* m_Property;
		MonoMethod* m_GetMethod;
		MonoMethod* m_SetMethod;
		MonoObject* m_Object;
	};
}