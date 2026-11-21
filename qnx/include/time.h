/* SPDX-License-Identifier: MPL-2.0 */
/* NBT toolchain, QNX 6.5 target: time. time_t is 32-bit unsigned. */
#ifndef _NBT_QNX_TIME_H
#define _NBT_QNX_TIME_H

#include <sys/_typedefs.h>

#define CLOCKS_PER_SEC 1000000
#define CLOCK_REALTIME 0
#define CLOCK_SOFTTIME 1
#define CLOCK_MONOTONIC 2
#define CLOCK_PROCESS_CPUTIME_ID 3
#define CLOCK_THREAD_CPUTIME_ID 4
#define TIMER_ABSTIME 0x80000000

struct itimerspec {
	struct timespec it_value;
	struct timespec it_interval;
};

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
	long int tm_gmtoff;
	const char *tm_zone;
};

struct sigevent;

__BEGIN_DECLS
char *asctime(const struct tm *__tp);
char *ctime(const time_t *__timer);
clock_t clock(void);
double difftime(time_t __t1, time_t __t0);
struct tm *gmtime(const time_t *__timer);
struct tm *localtime(const time_t *__timer);
time_t mktime(struct tm *__tp);
size_t strftime(char *__restrict __s, size_t __maxsize, const char *__restrict __fmt, const struct tm *__restrict __tp);
time_t time(time_t *__timer);

char *asctime_r(const struct tm *__restrict __tp, char *__restrict __buf);
char *ctime_r(const time_t *__timer, char *__buf);
struct tm *gmtime_r(const time_t *__restrict __timer, struct tm *__restrict __tm);
struct tm *localtime_r(const time_t *__restrict __timer, struct tm *__restrict __tm);
void tzset(void);

int clock_getres(clockid_t __clock_id, struct timespec *__res);
int clock_gettime(clockid_t __clock_id, struct timespec *__tp);
int clock_settime(clockid_t __clock_id, const struct timespec *__tp);
int clock_getcpuclockid(pid_t __pid, clockid_t *__clock_id);
int clock_nanosleep(clockid_t __clock_id, int __flags, const struct timespec *__rqtp, struct timespec *__rmtp);
int nanosleep(const struct timespec *__rqtp, struct timespec *__rmtp);
int timer_create(clockid_t __clock_id, struct sigevent *__restrict __evp, timer_t *__restrict __timerid);
int timer_delete(timer_t __timerid);
int timer_getoverrun(timer_t __timerid);
int timer_gettime(timer_t __timerid, struct itimerspec *__value);
int timer_settime(timer_t __timerid, int __flags, const struct itimerspec *__restrict __value, struct itimerspec *__restrict __ovalue);

/* QNX */
int nanosleep_abs(clockid_t __clock_id, const struct timespec *__rqtp);
int nanosleep_rel(clockid_t __clock_id, const struct timespec *__rqtp, struct timespec *__rmtp);
void nsec2timespec(struct timespec *__ts, _Uint64t __nsec);
_Uint64t timespec2nsec(const struct timespec *__ts);
int nanospin_ns(unsigned long __nsec);

char **__get_tzname_ptr(void);
int *__get_daylight_ptr(void);
long int *__get_timezone_ptr(void);
__END_DECLS
/* daylight and timezone are only reachable through the functions above:
 * as macros, timezone would rename struct timezone. */
#define tzname (__get_tzname_ptr())

#endif
