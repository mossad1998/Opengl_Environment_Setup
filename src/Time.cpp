#include "Time.h"

Time::Time()
{

}

double Time::calculateDeltaTime(std::chrono::high_resolution_clock::time_point startTime)
{
	std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
	long updateLength = (long)(std::chrono::duration_cast<std::chrono::nanoseconds>(now - startTime).count());
	lastLoopTime = now;
	double delta = updateLength / ((double)OPTIMAL_TIME);

    CalculateFPS(updateLength);

	return delta ;
}

void Time::CalculateFPS(long updateLength)
{
    // update the frame counter
    lastFpsTime += updateLength;
    fps++;

    // update our FPS counter if a second has passed since
    // we last recorded
    if (lastFpsTime >= 1000000000)
    {
        std::cout << fps<<std::endl;
        lastFpsTime = 0;
        fps = 0;
    }
}

std::chrono::high_resolution_clock::time_point Time::getLastLoopTime()
{
    return lastLoopTime;
}

const long Time::getOptimalTime()
{
    return OPTIMAL_TIME;
}
