/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: time of day and interval timers. */
#ifndef _NBT_QNX_SYS_TIME_H
#define _NBT_QNX_SYS_TIME_H

#include <sys/_typedefs.h>
#include <time.h>
#include <sys/select.h>

struct timeval {
	time_t tv_sec;
	suseconds_t tv_usec;
};

struct itimerval {
	struct timeval it_interval;
	struct timeval it_value;
};

struct timezone {
	int tz_minuteswest;
	int tz_dsttime;
};

#define ITIMER_REAL 0
#define ITIMER_VIRTUAL 1
#define ITIMER_PROF 2

#define timerclear(tvp) ((tvp)->tv_sec = (tvp)->tv_usec = 0)
#define timerisset(tvp) ((tvp)->tv_sec || (tvp)->tv_usec)
#define timercmp(tvp, uvp, cmp) \
	(((tvp)->tv_sec == (uvp)->tv_sec) ? ((tvp)->tv_usec cmp (uvp)->tv_usec) : ((tvp)->tv_sec cmp (uvp)->tv_sec))
#define timeradd(tvp, uvp, vvp) \
	do { \
		(vvp)->tv_sec = (tvp)->tv_sec + (uvp)->tv_sec; \
		(vvp)->tv_usec = (tvp)->tv_usec + (uvp)->tv_usec; \
		if ((vvp)->tv_usec >= 1000000) { \
			(vvp)->tv_sec++; \
			(vvp)->tv_usec -= 1000000; \
		} \
	} while (0)
#define timersub(tvp, uvp, vvp) \
	do { \
		(vvp)->tv_sec = (tvp)->tv_sec - (uvp)->tv_sec; \
		(vvp)->tv_usec = (tvp)->tv_usec - (uvp)->tv_usec; \
		if ((vvp)->tv_usec < 0) { \
			(vvp)->tv_sec--; \
			(vvp)->tv_usec += 1000000; \
		} \
	} while (0)

__BEGIN_DECLS
int getitimer(int __which, struct itimerval *__value);
int gettimeofday(struct timeval *__restrict __tp, void *__restrict __tzp);
int setitimer(int __which, const struct itimerval *__restrict __value, struct itimerval *__restrict __ovalue);
int settimeofday(const struct timeval *__tp, const struct timezone *__tzp);
int utimes(const char *__path, const struct timeval __times[2]);
__END_DECLS

#endif
