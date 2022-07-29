#pragma once
#include "Parameter.h"

namespace Spirit::Scripting {
	class Integer : public Parameter {
	public:
		Integer() = default;
		Integer(int value);
		
		Integer(const Integer& i) = default;
		Integer& operator=(const Integer& i) = default;

		operator int() const;
		virtual void* ptr() override;

	private:
		int m_Value = 0;
	};

	class UInt : public Parameter
	{
	public:
		UInt() = default;
		UInt(unsigned value);

		UInt(const UInt& i) = default;
		UInt& operator=(const UInt& i) = default;

		operator unsigned() const;
		virtual void* ptr() override;
	private:
		unsigned m_Value = 0;
	};

	class Float : public Parameter
	{
	public:
		Float() = default;
		Float(float value);

		Float(const Float& f) = default;
		Float& operator=(const Float& f) = default;


		operator float() const;
		virtual void* ptr() override;
	private:
		float m_Value = 0;
	};

	class Double : public Parameter
	{
	public:
		Double() = default;
		Double(double value);

		Double(const Double& d) = default;
		Double& operator=(const Double& d) = default;

		operator double() const;
		virtual void* ptr() override;
	private:
		double m_Value = 0;
	};

	class String : public Parameter
	{
	public:
		String() = default;
		String(std::string value);

		String(const String& d) = default;
		String& operator=(const String& d) = default;

		operator std::string() const;
		virtual void* ptr() override;
	private:
		std::string m_Value = "";
	};

}