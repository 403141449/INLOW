#ifndef _TIME_H
#define _TIME_H

#include <sys/cdefs.h>

#define __need_clock_t
#define __need_locale_t
#define __need_NULL
#define __need_size_t
#define __need_time_t
#if __USE_INLOW || _USE_POSIX
#define __need_clockid_t
#define __need_timer_t
#endif

#include <sys/libc-types.h>
#include <inlow/timespec.h>

#ifdef __cplusplus
extern "C"
{
#endif

#if __USE_INLOW || __USE_POSIX
		int nanosleep(const struct timespec*, struct timespec*);
#endif

#ifdef __cplusplus
}
#endif

#endif
