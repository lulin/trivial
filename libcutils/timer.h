/*
 * Copyright (c) 2014
 *
 * "License"
 *
 * Bug reports and issues: <"Email">
 *
 * This file is part of cwfragment.
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>
#include <stdlib.h>

struct timer {
	enum {
		timer_stat_started,
		timer_stat_stopped
	} state;
	struct timeval start;
	struct timeval end;
};

#define SECOND 1000000
#define timer_is_stopped(t) ((t)->state == timer_stat_stopped)
#define timer_is_started(t) ((t)->state == timer_stat_started)

static inline void timer_start(struct timer *timer)
{
	if (!timer)
		return;
	timer->state = timer_stat_started;
	gettimeofday(&timer->start, NULL);
}

static inline struct timer *timer_new()
{
	struct timer *timer = malloc(sizeof(struct timer));
	timer_start(timer);
	return timer;
}

static inline void timer_stop(struct timer *timer)
{
	if (!timer)
		return;
	timer->state = timer_stat_stopped;
	gettimeofday(&timer->end, NULL);
	return;
}

static inline void timer_continue(struct timer *timer)
{
	if (!timer || timer_is_started(timer))
		return;
	timer->state = timer_stat_started;
	gettimeofday(&timer->start, NULL);
	return;
}

static inline unsigned long timer_elapsed(struct timer *timer,
	struct timeval *elapsed)
{
	unsigned long seconds;
	struct timeval now;
	struct timeval _e;

	if (!timer)
		return 0;

	if (timer_is_stopped(timer)) {
		_e.tv_sec = timer->end.tv_sec - timer->start.tv_sec;
		_e.tv_usec = timer->end.tv_usec - timer->start.tv_usec;
	} else {
		gettimeofday(&now, NULL);
		_e.tv_sec = now.tv_sec - timer->start.tv_sec;
		_e.tv_usec = now.tv_usec - timer->start.tv_usec;
	}

	if (_e.tv_usec < 0) {
		_e.tv_sec--;
		_e.tv_usec += SECOND;
	}

	if (_e.tv_sec < 0) {
		_e.tv_sec = 0;
		_e.tv_usec = 0;
	}

	seconds = _e.tv_sec * SECOND + _e.tv_usec;
	if (elapsed) {
		elapsed->tv_sec = _e.tv_sec;
		elapsed->tv_usec = _e.tv_usec;
	}
	return seconds;
}

static inline void timer_destroy(struct timer **ptimer)
{
	if (ptimer && *ptimer) {
		free(*ptimer);
		*ptimer = NULL;
	}
}

#endif /* TIMER_H_ */













