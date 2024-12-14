#include "Time.h"

Time::Time()
{
}

Time::~Time()
{
}
double Time::getDeltaTime()
{
	return m_deltaTime;
}


void Time::CalculateDeltaTime(double currentTime)
{
	m_deltaTime = currentTime - m_oldTime;
	m_oldTime = currentTime;
}
