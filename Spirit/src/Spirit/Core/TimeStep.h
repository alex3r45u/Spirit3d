#pragma once


namespace Spirit {
	class TimeStep {
	public:
		TimeStep(float time) : m_Time(time) {}
		float GetSeconds() { return m_Time; }
		float GetMilliSeconds() { return m_Time * 1000.0f; }
		operator float() { return m_Time; }
	private:
		float m_Time;
	};
}