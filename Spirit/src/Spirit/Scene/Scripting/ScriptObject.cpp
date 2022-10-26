#include "sppch.h"
#include "ScriptObject.h"
#include "ScriptMethod.h"
#include "ScriptField.h"
#include "ScriptProperty.h"
#include "ScriptClass.h"


Spirit::Scripting::ScriptObject::ScriptObject(MonoObject* object, const std::unordered_map<std::string, std::shared_ptr<ScriptMethod>>& methods)
    : m_Object(object), m_Methods(methods)
{
}

void Spirit::Scripting::ScriptObject::Invoke(const std::string& method, ParameterList params)
{
    auto iter = m_Methods.find(method);

    if (iter != m_Methods.end())
        iter->second->Invoke(params, this);
}

MonoObject* Spirit::Scripting::ScriptObject::GetObjectPointer() const
{
    return m_Object;
}

std::string Spirit::Scripting::ScriptObject::GetTypeName() const
{
    return mono_type_get_name(mono_class_get_type(mono_object_get_class(m_Object)));
}

Spirit::Scripting::ScriptProperty& Spirit::Scripting::ScriptObject::GetProperty(const std::string& name)
{
    auto iter = m_Properties.find(name);
    if (iter != m_Properties.end())
        return *iter->second;
    else
    {
        MonoClass* pClass = mono_object_get_class(m_Object);
        MonoProperty* pProperty = nullptr;
        pProperty = mono_class_get_property_from_name(pClass, name.c_str());
        if (pProperty == nullptr)
            SP_CORE_ERROR("Cannot find property: " + name);

        auto prop = std::make_shared<ScriptProperty>(m_Object, pProperty);
        m_Properties[name] = prop;
        return *prop;
    }
}



static Spirit::Scripting::FieldType GetFieldType(MonoType* monoType) {
    int type = mono_type_get_type(monoType);
    switch (type)
    {
    case MONO_TYPE_R4: return Spirit::Scripting::FieldType::Float;
    case MONO_TYPE_I4: return Spirit::Scripting::FieldType::Int;
    case MONO_TYPE_U4: return Spirit::Scripting::FieldType::UnsignedInt;
    case MONO_TYPE_STRING: return Spirit::Scripting::FieldType::String;
    case MONO_TYPE_BOOLEAN: return Spirit::Scripting::FieldType::Bool;

    case MONO_TYPE_VALUETYPE:
    {
        char* name = mono_type_get_name(monoType);
        if (strcmp(name, "SpiritScript.Math.Vector2") == 0) return Spirit::Scripting::FieldType::Vec2;
        if (strcmp(name, "SpiritScript.Math.Vector3") == 0) return Spirit::Scripting::FieldType::Vec3;
        if (strcmp(name, "SpiritScript.Math.Vector4") == 0) return Spirit::Scripting::FieldType::Vec4;
    }
    }
    return Spirit::Scripting::FieldType::Unknown;
}

Spirit::Scripting::ScriptField& Spirit::Scripting::ScriptObject::GetField(const std::string& name)
{
    auto iter = m_Fields.find(name);

    if (iter != m_Fields.end())
        return *iter->second;
    else
    {
        MonoClass* pClass = mono_object_get_class(m_Object);
        MonoClassField* pField = mono_class_get_field_from_name(pClass, name.c_str());


        if (pField == nullptr)
            SP_CORE_ERROR("Couldn't find field: " + name);

        MonoType* fieldType = mono_field_get_type(pField);
        FieldType spiritFieldType = GetFieldType(fieldType);

        auto field = std::make_shared<ScriptField>(m_Object, pField, spiritFieldType);
        m_Fields[name] = field;
        return *field;
    }

}

bool Spirit::Scripting::ScriptObject::FieldExists(const std::string& name)
{
    auto iter = m_Fields.find(name);

    if (iter != m_Fields.end())
        return true;
    MonoClass* pClass = mono_object_get_class(m_Object);
    MonoClassField* pField = mono_class_get_field_from_name(pClass, name.c_str());


    if (pField == nullptr)
        return false;
    return true;
}

Spirit::Scripting::ScriptClass& Spirit::Scripting::ScriptObject::GetClass()
{
    return Spirit::Scripting::ScriptClass(mono_object_get_class(m_Object), mono_domain_get());
}

