#include "TimeHelper.h"

float TimeHelper::GetAllTime()
{
	return allTime;
}

float TimeHelper::GetThisTickTime() const
{
	return thisTickTime;
}

bool TimeHelper::GetIsRuning()
{
	return isRuning;
}

void TimeHelper::Reset()
{
	isRuning = false;
	allTime = 0;
}

void TimeHelper::Start()
{
	isRuning = true;
	lastTickClock = clock();
}

void TimeHelper::Stop()
{
	isRuning = false;
}

void TimeHelper::Tick()
{
	if (!isRuning)
	{
		return;
	}
	clock_t newTickClock = clock();
	thisTickTime = (float)(newTickClock - lastTickClock)/ CLOCKS_PER_SEC;
	allTime += thisTickTime;
	lastTickClock = newTickClock;
}