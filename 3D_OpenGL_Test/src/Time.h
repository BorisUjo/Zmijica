#pragma once

class Time
{
private:
	double m_deltaTime;
	double m_oldTime;

public:
	Time();
	~Time();
	void CalculateDeltaTime(double currentTime);
	double getDeltaTime();
};