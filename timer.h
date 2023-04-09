#include <SDL.h>

class LTimer
{
public:
	LTimer();
	~LTimer();

	//The various clock actions
	void start();
	void stop();
	void pause();
	void unpause();

	Uint32 getTicks();

	bool isStarted();
	bool isPaused();

private:
	//The clock time when the timer started
	Uint32 mStartedTicks;

	//The ticks stored when the timer was paused
	Uint32 mPausedTicks;

	//The timer status
	bool mPaused;
	bool mStarted;
};