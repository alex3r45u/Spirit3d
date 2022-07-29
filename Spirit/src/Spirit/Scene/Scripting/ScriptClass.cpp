#include "sppch.h"
#include "ScriptClass.h"

#include <mono/metadata/attrdefs.h>

Spirit::Scripting::ScriptClass::ScriptClass(MonoClass* _class, MonoDomain* domain)
    : m_Class(_class), m_Domain(domain)
{
    MonoMethod* m;
    MonoClassField* f;
    void* iter = nullptr;
    while ((m = mono_class_get_methods(m_Class, &iter)) != nullptr) {
        m_Methods[mono_method_get_name(m)] = std::make_shared<ScriptMethod>(m);
    }
}


Spirit::Scripting::ScriptObject Spirit::Scripting::ScriptClass::CreateInstance()
{
    MonoObject* object = mono_object_new(m_Domain, m_Class);

    mono_runtime_object_init(object);

    return ScriptObject(object, m_Methods);
}

void Spirit::Scripting::ScriptClass::Invoke(const std::string& method, ParameterList params)
{
    auto iter = m_Methods.find(method);

    if (iter != m_Methods.end())
        iter->second->Invoke(params, nullptr);
    else
        SP_CORE_ERROR("Cannot find method: " + method);
}

std::string Spirit::Scripting::ScriptClass::GetName() const
{
    return mono_class_get_name(m_Class);
}

std::vector<std::string> Spirit::Scripting::ScriptClass::GetFieldNames() const
{
    std::vector<std::string> _Fields;

    MonoClassField* field;
    void* iter = nullptr;

    while ((field = mono_class_get_fields(m_Class, &iter)) != nullptr)
    {
        if ((mono_field_get_flags(field) & MONO_FIELD_ATTR_PUBLIC) == 0)
            continue;
        _Fields.push_back(mono_field_get_name(field));
    }



    return _Fields;
}

std::vector<std::string> Spirit::Scripting::ScriptClass::GetMethodNames() const
{
    std::vector<std::string> _Methods;

    MonoMethod* method;
    void* iter = nullptr;

    while ((method = mono_class_get_methods(m_Class, &iter)) != nullptr)
        _Methods.push_back(mono_method_get_name(method));

    return _Methods;
}

std::vector<std::string> Spirit::Scripting::ScriptClass::GetPropertyNames() const
{
    std::vector<std::string> _Properties;

    MonoProperty* property;
    void* iter = nullptr;

    while ((property = mono_class_get_properties(m_Class, &iter)) != nullptr)
        _Properties.push_back(mono_property_get_name(property));

    return _Properties;
}

std::vector<std::string> Spirit::Scripting::ScriptClass::GetEventNames() const
{
    std::vector<std::string> _Events;

    MonoEvent* event;
    void* iter = nullptr;

    while ((event = mono_class_get_events(m_Class, &iter)) != nullptr)
        _Events.push_back(mono_event_get_name(event));

    return _Events;
}

std::unordered_map<std::string, std::shared_ptr<Spirit::Scripting::ScriptMethod>> Spirit::Scripting::ScriptClass::GetAllMethods() const
{
    return m_Methods;
}

