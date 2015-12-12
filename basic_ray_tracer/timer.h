#ifndef TIMER_H
#define TIMER_H

#include <ctime>
#include <sys/time.h>

// Simple timer.
class ClockTimer
{
private:
    struct timeval start;

public:
    ClockTimer (void);

    void reset (void);
    static struct timeval now (void);
    std::size_t get_elapsed (void) const;
};

/* ------------------------ Implementation ------------------------ */

inline
ClockTimer::ClockTimer (void)
{
    this->reset();
}

inline void
ClockTimer::reset (void)
{
    this->start = ClockTimer::now();
}

inline struct timeval
ClockTimer::now (void)
{
  struct timeval now;
  gettimeofday(&now, NULL);
  return now;
}

inline std::size_t
ClockTimer::get_elapsed (void) const
{
    return (ClockTimer::now().tv_sec - start.tv_sec) *1000 + (ClockTimer::now().tv_usec - start.tv_usec)  / 1000;
}

#endif // TIMER_H
