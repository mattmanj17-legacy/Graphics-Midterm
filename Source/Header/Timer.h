#ifndef TIMER_H
#define TIMER_H

#include <chrono>
using namespace std::chrono;

class Timer
{
private:
	float max_dt;
	long long currentTime_ms;

public:
	float currentTime;
	float deltaTime;

	Timer()
	{
		max_dt= 0.1;
		deltaTime = 0;

		auto duration = system_clock::now().time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	
		currentTime_ms = millis;
		currentTime = (float)millis / 1000;
	}

	void Update()
	{
		auto duration = system_clock::now().time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

		int delta_ms = millis - currentTime_ms;
		deltaTime = min((float)delta_ms / 1000, max_dt);
		
		currentTime_ms = millis;
		currentTime = (float)millis / 1000;
	}

};

#endif