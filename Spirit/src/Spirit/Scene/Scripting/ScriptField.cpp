#include "sppch.h"
#include "ScriptField.h"


std::string Spirit::Scripting::ScriptField::GetName()
{
    return std::string(mono_class_get_name(mono_object_get_class(m_Object))) + "::" + mono_field_get_name(m_Field);
}
