#include "Timer.hpp"
#include "SDL.hpp"

Timer::Timer()
{
    this->startMark  = 0;
    this->stopMark   = 0;
    this->pausedMark = 0;
    this->running    = false;
    this->paused     = false;
}
void Timer::start()
{
    if (this->running) return;

    this->startMark  = SDL_GetTicks();
    this->stopMark   = 0;
    this->pausedMark = 0;
    this->running    = true;
    this->paused     = false;
}
void Timer::stop()
{
    if (!this->running) return;

    this->stopMark = SDL_GetTicks();
    this->running  = false;
    this->paused   = false;
}
void Timer::restart()
{
    this->stop();
    this->start();
}
void Timer::pause()
{
    if (!running || paused) return;

    this->running    = false;
    this->paused     = true;
    this->pausedMark = (SDL_GetTicks()) - (this->startMark);
}
void Timer::unpause()
{
    if (!paused || running) return;

    this->running = true;
    this->paused  = false;

    this->startMark  = (SDL_GetTicks()) - (this->pausedMark);
    this->pausedMark = 0;
}
bool Timer::isRunning()
{
    return this->running;
}
bool Timer::isPaused()
{
    return this->paused;
}
uint32_t Timer::delta()
{
    if (this->isRunning())
        return this->currentTime();

    if (this->paused)
        return this->pausedMark;

    // Something went wrong here
    if (this->startMark == 0)
        return 0;

    return (this->stopMark) - (this->startMark);
}
uint32_t Timer::delta_ms()
{
    return this->delta() % 1000;
}
uint32_t Timer::delta_s()
{
    return this->delta() / 1000;
}
uint32_t Timer::currentTime()
{
    return (SDL_GetTicks()) - (this->startMark);
}

