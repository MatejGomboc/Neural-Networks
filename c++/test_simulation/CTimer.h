#ifndef CTIMER_H
#define CTIMER_H

//-----------------------------------------------------------------------
//
//  Name: CTimer.h
//
//	Desc: Windows timer class
//
//-----------------------------------------------------------------------

class CTimer
{
private:
	LONGLONG m_CurrentTime;
	LONGLONG m_LastTime;
	LONGLONG m_NextTime;
	LONGLONG m_FrameTime;
	LONGLONG m_PerfCountFreq;

	double m_TimeElapsed;
	double m_TimeScale;
	float m_FPS;

public:
	//ctors
	CTimer();
	CTimer(float fps);

	//this starts the timer
	void Start();

	//determines if enough time has passed to move onto next frame
	bool ReadyForNextFrame();

	//only use this after a call to the above.
	double	GetTimeElapsed(){return m_TimeElapsed;}

	double	TimeElapsed();
};

#endif