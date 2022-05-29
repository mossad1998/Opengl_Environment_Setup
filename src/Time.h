#pragma once

#include <iostream>
#include <chrono>

class Time {

	private:
		const int TARGET_FPS = 60;
		const long OPTIMAL_TIME = 1000000000 / TARGET_FPS;
		std::chrono::high_resolution_clock::time_point lastLoopTime;
		long lastFpsTime = 0;
		long fps = 0;

	public:
		Time();
		double calculateDeltaTime(std::chrono::high_resolution_clock::time_point startTime);
		void CalculateFPS(long updateLength);
		std::chrono::high_resolution_clock::time_point getLastLoopTime();
		const long getOptimalTime();

};