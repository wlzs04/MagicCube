#pragma once
#include<ctime>

using namespace std;

//计时器
class TimeHelper
{
public:
	float GetAllTime();
	float GetThisTickTime()const;

	bool GetIsRuning();

	void Reset();
	void Start();
	void Stop();
	void Tick();

private:
	bool isRuning = false;

	clock_t lastTickClock = 0;
	float thisTickTime = 0;
	float allTime = 0;
};

