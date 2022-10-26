#include "sppch.h"
#include "ScriptDomain.h"
#include "Spirit/Application.h"
#include "Spirit/Core/File.h"

Spirit::Scripting::ScriptDomain::ScriptDomain(std::string filename, std::string filenameCore)
{
	mono_set_dirs("mono/lib", ".");
	m_Root = mono_jit_init("SpiritScriptRoot");
	
	InitAssemblies(filename, filenameCore);

	
}

Spirit::Scripting::ScriptDomain::~ScriptDomain()
{
	mono_jit_cleanup(m_Root);
}

void Spirit::Scripting::ScriptDomain::Reload(std::string filename, std::string filenameCore)
{
	Unload();
	Load(filename, filenameCore);
}

void Spirit::Scripting::ScriptDomain::Unload()
{
	mono_domain_set(m_Root, 0);
	m_Classes = {};
	mono_domain_unload(m_Domain);
}

void Spirit::Scripting::ScriptDomain::Load(std::string filename, std::string filenameCore)
{
	InitAssemblies(filename, filenameCore);
}

Spirit::Scripting::ScriptClass& Spirit::Scripting::ScriptDomain::GetClass(const std::string& name)
{
	auto iter = m_Classes.find(name);
	size_t dotPos = name.find_last_of('.');

	if (dotPos == std::string::npos)
		SP_CORE_ERROR("Failed to find class {0}", name);

	std::string name_space = name.substr(0, dotPos);
	std::string class_name = name.substr(dotPos + 1);

	if (iter != m_Classes.end())
		return *iter->second;


	else
	{
		MonoClass* pClass = mono_class_from_name(name_space == "SpiritScript" ? m_CoreImage : m_Image, name_space.c_str(), class_name.c_str());
			if (pClass == nullptr)
				SP_CORE_ERROR("Failed to find class {0}", name);
		

		auto _class = std::make_shared<ScriptClass>(pClass, m_Domain);
		m_Classes[name] = _class;

		return *_class;
	}
}

Spirit::Scripting::ScriptObject& Spirit::Scripting::ScriptDomain::GetObjectOutMonoObject(MonoObject* object)
{
	MonoClass* _class = mono_object_get_class(object);
	ScriptClass sclass = ScriptClass(_class, m_Domain);
	return ScriptObject(object, sclass.GetAllMethods());
}

bool Spirit::Scripting::ScriptDomain::ClassExist(const std::string& name)
{
	size_t dotPos = name.find_last_of('.');

	if (dotPos == std::string::npos)
		return false;

	std::string name_space = name.substr(0, dotPos);
	std::string class_name = name.substr(dotPos + 1);

	MonoClass* pClass = mono_class_from_name(m_Image, name_space.c_str(), class_name.c_str());

	return pClass != nullptr;
}

void Spirit::Scripting::ScriptDomain::InitAssemblies(std::string filename, std::string filenameCore)
{
	
	m_Domain = mono_domain_create_appdomain("SpiritScript", NULL);
	mono_domain_set(m_Domain, true);
	if (!m_Domain)
		SP_CORE_ERROR("m_Domain is null");

	m_Assembly = mono_domain_assembly_open(m_Domain, Spirit::File::Merge2Paths(PROJECT->GetSettings().Path, PROJECT->GetSettings().ProjectName + ".dll").string().c_str());

	if (!m_Assembly)
		SP_CORE_ERROR("m_Assembly is null");

	m_Image = mono_assembly_get_image(m_Assembly);

	if (!m_Image)
		SP_CORE_ERROR("m_Image is null");

	//Core
	m_CoreAssembly = mono_domain_assembly_open(m_Domain, Spirit::File::Merge2Paths(PROJECT->GetSettings().Path, "SpiritScript.dll").string().c_str());

	if (!m_CoreAssembly)
		SP_CORE_ERROR("m_CoreAssembly is null");

	m_CoreImage = mono_assembly_get_image(m_CoreAssembly);

	if (!m_CoreImage)
		SP_CORE_ERROR("m_CoreImage is null");
	
}
