#pragma once

class Time_Stamp {

	public :
		Time_Stamp(float time = 0.0) 
			:m_time(time)
		{
		}

		float GetSeconds() const { return m_time; }
		float GetMilliseconds() const { return m_time * 1000.0f; }

	private:
		float m_time;
};