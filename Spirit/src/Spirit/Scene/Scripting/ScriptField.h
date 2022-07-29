#pragma once
#include <string>
#include <mono/jit/jit.h>

#include <mono/metadata/object.h>
#include <mono/metadata/environment.h>
#include <mono/utils/mono-publib.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>


namespace Spirit::Scripting {
	enum class FieldType
	{
		None = 0,
		Unknown = 1,
		Int,
		UnsignedInt,
		Float,
		Bool,
		String,
		Vec2,
		Vec3,
		Vec4
	}; 
	class ScriptField {
	public:
		ScriptField(MonoObject* object, MonoClassField* field, FieldType type) : m_Field(field), m_Object(object), m_Type(type) {}

		std::string GetName();
		FieldType GetType()  { return m_Type; }

		template<typename T>
		void SetValue(T value) {
			mono_field_set_value(m_Object, m_Field, &value);
		}

		template<typename T>
		T GetValue() const
		{
			T value;
			mono_field_get_value(m_Object, m_Field, &value);
			return value;
		}

		template<>
		void SetValue(std::string str)
		{
			mono_field_set_value(m_Object, m_Field, mono_string_new(mono_domain_get(), str.c_str()));
		}

		template<>
		std::string GetValue() const
		{
			MonoString* str;
			mono_field_get_value(m_Object, m_Field, &str);
			return std::string(mono_string_to_utf8(str));
		}

	private:
		MonoClassField* m_Field = nullptr;
		MonoObject* m_Object = nullptr;
		FieldType m_Type = FieldType::None;
	};
}