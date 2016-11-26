#include "timer.h"

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers.
#include <windows.h>

#include <exception>


namespace Simulation
{
	//---------------------- default constructor ------------------------------
	Timer::Timer() :
		m_fFPS(0),
		m_dTimeElapsed(0.0),
		m_llFrameTime(0),
		m_llLastTime(0),
		m_llPerfCountFreq(0)
	{
		//how many ticks per sec do we get
		QueryPerformanceFrequency((LARGE_INTEGER*)& m_llPerfCountFreq);

		m_dTimeScale = 1.0 / static_cast<double>(m_llPerfCountFreq);
	}



	//---------------------- constructor -------------------------------------
	//	Use to specify FPS.
	//-------------------------------------------------------------------------
	Timer::Timer(const float fps) :
		m_fFPS(fps),
		m_dTimeElapsed(0.0),
		m_llLastTime(0),
		m_llPerfCountFreq(0)
	{
		//how many ticks per sec do we get
		QueryPerformanceFrequency((LARGE_INTEGER*)& m_llPerfCountFreq);

		m_dTimeScale = 1.0 / static_cast<double>(m_llPerfCountFreq);

		//calculate ticks per frame
		m_llFrameTime = static_cast<LONGLONG>(static_cast<float>(m_llPerfCountFreq) / m_fFPS);
	}



	//------------------------Start()-----------------------------------------
	//	Call this immediately prior to simulation loop. Starts the timer.
	//--------------------------------------------------------------------------
	void Timer::start()
	{
		//get the time
		QueryPerformanceCounter((LARGE_INTEGER*)& m_llLastTime);

		//update time to render next frame
		m_llNextTime = m_llLastTime + m_llFrameTime;

		return;
	}



	//-------------------------ReadyForNextFrame()-------------------------------
	//	Returns true if it is time to move on to the next frame step. To be used if
	//	FPS is set.
	//----------------------------------------------------------------------------

	bool Timer::readyForNextFrame()
	{
		if (m_fFPS == 0.0f) throw(std::exception("No FPS set in timer."));

		QueryPerformanceCounter((LARGE_INTEGER*)& m_llCurrentTime);

		if (m_llCurrentTime > m_llNextTime)
		{
			m_dTimeElapsed = static_cast<double>(m_llCurrentTime - m_llLastTime) * m_dTimeScale;
			m_llLastTime   = m_llCurrentTime;

			//update time to render next frame
			m_llNextTime = m_llCurrentTime + m_llFrameTime;

			return true;
		}

		return false;
	}



	//--------------------------- GetTimeElapsed --------------------------------
	//	Only use this after a call to the above.
	//-------------------------------------------------------------------------
	double Timer::getTimeElapsed() const
	{
		return m_dTimeElapsed;
	}



	//--------------------------- TimeElapsed --------------------------------
	//	Returns time elapsed since last call to this function. Use in main
	//	when calculations are to be based on dt.
	//-------------------------------------------------------------------------
	double Timer::timeElapsed()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)& m_llCurrentTime);

		m_dTimeElapsed = static_cast<double>(m_llCurrentTime - m_llLastTime) * m_dTimeScale;

		m_llLastTime = m_llCurrentTime;

		return m_dTimeElapsed;
	}



	//--------------------------- GetFPS --------------------------------------
	//	Only use this after a call to the above.
	//-------------------------------------------------------------------------
	float Timer::getFPS() const
	{
		return m_fFPS;
	}
}
