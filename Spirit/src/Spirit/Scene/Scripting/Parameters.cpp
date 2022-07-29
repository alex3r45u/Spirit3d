#include "sppch.h"
#include "Parameters.h"

Spirit::Scripting::Integer::Integer(int value)
	: m_Value(value)
{
}

Spirit::Scripting::Integer::operator int() const
{
	return m_Value;
}

void* Spirit::Scripting::Integer::ptr()
{
	return &m_Value;
}

Spirit::Scripting::UInt::UInt(unsigned value)
	: m_Value(value)
{
}

Spirit::Scripting::UInt::operator unsigned() const
{
	return m_Value;
}

void* Spirit::Scripting::UInt::ptr()
{
	return &m_Value;
}

Spirit::Scripting::Float::Float(float value)
	: m_Value(value)
{
}

Spirit::Scripting::Float::operator float() const
{
	return m_Value;
}

void* Spirit::Scripting::Float::ptr()
{
	return &m_Value;
}

Spirit::Scripting::Double::Double(double value)
	: m_Value(value)
{
}

Spirit::Scripting::Double::operator double() const
{
	return m_Value;
}

void* Spirit::Scripting::Double::ptr()
{
	return &m_Value;
}

Spirit::Scripting::String::String(std::string value)
{
	m_Value = value;
}

Spirit::Scripting::String::operator std::string() const
{
	return m_Value;
}

void* Spirit::Scripting::String::ptr()
{
	return &m_Value;
}
