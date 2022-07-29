#include "sppch.h"
#include "ParameterList.h"
#include "Parameters.h"

Spirit::Scripting::ParameterList& Spirit::Scripting::ParameterList::Append(int value)
{
    m_Parameters.emplace_back(std::make_shared<Integer>(value));
    return *this;
}

Spirit::Scripting::ParameterList& Spirit::Scripting::ParameterList::Append(float value)
{
    m_Parameters.emplace_back(std::make_shared<Float>(value));
    return *this;
}

Spirit::Scripting::ParameterList& Spirit::Scripting::ParameterList::Append(double value)
{
    m_Parameters.emplace_back(std::make_shared<Double>(value));
    return *this;
}

Spirit::Scripting::ParameterList& Spirit::Scripting::ParameterList::Append(const char* value)
{
    m_Parameters.emplace_back(std::make_shared<String>(value));
    return *this;
}

void Spirit::Scripting::ParameterList::Reserve(int size)
{
}

int Spirit::Scripting::ParameterList::Size() const
{
    return 0;
}

void** Spirit::Scripting::ParameterList::GetArgs()
{
    return nullptr;
}

Spirit::Scripting::ParameterList::~ParameterList()
{
}
