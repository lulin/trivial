#ifndef __ETIMER_H__
#define __ETIMER_H__

#include <sys/time.h>
#include <stdlib.h>

enum ETIMER_STATE {
	ETIMER_INIT,
	ETIMER_STARTED,
	ETIMER_STOPPED,
	ETIMER_PAUSED,
	ETIMER_RECOVERY,
};
struct etimer {
	enum ETIMER_STATE state;

	struct timeval start;
	struct timeval recover;
	struct timeval pause;
	struct timeval stop;

	long elapsed;
};

#define MILLION 1000000
#define TIMEVAL_RESET(t) do {(t).tv_sec=(t).tv_usec=0} while (0)
#define TIMEVAL_AFTER(n,p) \
	(((n).tv_sec * MILLION - (p).tv_sec * MILLION) + \
	((n).tv_usec - (p).tv_usec))
//static inline long timeval_after(struct timeval *n, struct timeval *p)
//{
//	if (!p || !n)
//		return -1;
//	long val;
//	val = (n->tv_sec - p->tv_sec) * MILLION;
//	val += n->tv_usec - p->tv_usec;
//	return val;
//}

static inline struct etimer *etimer_new()
{
	struct etimer *etimer;
	etimer = (struct etimer*)malloc(sizeof(struct etimer));
	etimer->state = ETIMER_INIT;
	etimer->elapsed = 0;
}

static inline struct etimer *etimer_start(struct etimer *etimer)
{
	if (etimer == NULL) {
		etimer = etimer_new();
	}

	if (etimer == ETIMER_STOPPED)

	if (etimer->state == ETIMER_INIT) {
		etimer->state = ETIMER_STARTED;
		gettimeofday(&etimer->start, 0);
		//RESET_TIMEVAL(etimer->pause);
		//RESET_TIMEVAL(etimer->stop);
	}

	return etimer;
}

static inline void etimer_pause(struct etimer *etimer)
{
	if (!etimer || etimer->state != ETIMER_STARTED ||
		etimer->state != ETIMER_RECOVERY)
		return;

	etimer->state = ETIMER_PAUSED;
	gettimeofday(&etimer->pause, 0);
	etimer->elapsed += TIMEVAL_AFTER(etimer->pause, etimer->recover);
	return;
}

static inline void etimer_recover(struct etimer *etimer)
{
	if (!etimer || etimer->state != ETIMER_STARTED ||
		etimer->state != ETIMER_RECOVERY)
		return;
}

static inline void etimer_stop(struct etimer *etimer)
{
	if (!etimer || etimer->state == ETIMER_INIT ||
		etimer->state == ETIMER_STOPPED)
		return;

	etimer->state = ETIMER_STOPPED;
	gettimeofday(&etimer->stop, 0);
	etimer->elapsed = TIMEVAL_AFTER(etimer->stop, etimer->start);
	return;
}

static inline long etimer_elapsed(struct etimer *etimer)
{
	if (etimer->state == ETIMER_INIT)
		return 0;

	if (etimer->state == ETIMER_STOPPED) {
		return etimer->elapsed;
	}

	return TIMEVAL_AFTER(etimer->stop, etimer->start);
}
#endif
