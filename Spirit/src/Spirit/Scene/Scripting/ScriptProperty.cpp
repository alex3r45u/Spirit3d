#include "sppch.h"
#include "ScriptProperty.h"

Spirit::Scripting::ScriptProperty::ScriptProperty(MonoObject* object, MonoProperty* _property)
	: m_Property(_property), m_Object(object)
{
	m_GetMethod = mono_property_get_get_method(m_Property);
	m_SetMethod = mono_property_get_set_method(m_Property);
}

std::string Spirit::Scripting::ScriptProperty::GetName() const
{
	return  std::string(mono_class_get_name(mono_object_get_class(m_Object))) + "::" + mono_property_get_name(m_Property);
}

bool Spirit::Scripting::ScriptProperty::HasSetProperty() const
{
	return m_SetMethod != nullptr;
}

bool Spirit::Scripting::ScriptProperty::HasGetProperty() const
{
	return m_GetMethod != nullptr;
}
