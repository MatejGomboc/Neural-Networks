#pragma once

//#include "targetver.h"
//#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers.
#include <windows.h>


namespace Simulation
{
	class Timer
	{
	private:
		LONGLONG m_llCurrentTime;
		LONGLONG m_llLastTime;
		LONGLONG m_llNextTime;
		LONGLONG m_llFrameTime;
		LONGLONG m_llPerfCountFreq;

		double m_dTimeElapsed;
		double m_dTimeScale;

		float m_fFPS;

	public:
		//ctors
		Timer();
		Timer(const float fps);

		//starts the timer
		void start();

		//determines if enough time has passed to move onto next frame
		bool readyForNextFrame();

		//only use this after a call to the above
		double getTimeElapsed() const;

		double timeElapsed();

		float getFPS() const;
	};
};
