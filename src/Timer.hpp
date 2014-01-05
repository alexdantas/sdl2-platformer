#ifndef TIMER_H_DEFINED
#define TIMER_H_DEFINED

#include <string>
#include <sstream>
#include "stdint.h" // for uint32_t

/// General-purpose timer, measured in milisseconds.
///
///	## How to use:
///
///	    Timer timer;
///	    timer.start();
///	    // ...
///	    timer.pause();
///	    // ...
///	    timer.unpause();
///	    // ...
///	    timer.stop();
///	    int delta = timer.delta();
///
class Timer
{
public:
	Timer();

	/// Sets a starting point for the timer.
	void start();

	/// Sets a stopping point for the timer.
	void stop();

	/// Temporarily stops the timer.
	void pause();

	/// Stops and starts the timer.
	void restart();

	/// Restarts the timer if it was paused.
	void unpause();

	/// Tells if the timer's still running (hasn't called stop())
	bool isRunning();

	/// Tells if the timer's paused.
	bool isPaused();

	/// Returns the whole timer's difference in milisseconds.
	//	@note If the timer's not started, will return 0.
	uint32_t delta();

	/// Returns the milisseconds part of the timer's difference.
	uint32_t delta_ms();

	/// Returns the seconds part of the timer's difference.
	uint32_t delta_s();

	/// Returns the difference between timer's start point and now.
	uint32_t currentTime();

protected:
	uint32_t startMark;
	uint32_t stopMark;
	uint32_t pausedMark;

	bool running;
	bool paused;
};

#endif /* TIMER_H_DEFINED */

