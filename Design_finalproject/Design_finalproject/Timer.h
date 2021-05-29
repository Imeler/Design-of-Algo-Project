#pragma once
#ifndef TIMER_H

#define TIMER_H

#include <string>

#include <ctime>

#include <ratio>

#include <chrono>

class Timer

{

public:

	Timer() {} // default constructor

	~Timer() {} // destructor

	void markTime() { start = std::clock(); }

	double getTime() const {
		return((std::clock() - start) /

			(double)CLOCKS_PER_SEC);
	}

private:

	std::clock_t start; // the time stamp

};

#endif

