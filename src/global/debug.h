#ifndef DEBUG_H
#define DEBUG_H

#include "stdio.h"

#define __FILENAME__                                                           \
	(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#if true
#define __log_internal(level, msg, ...)                                        \
	printf(                                                                    \
		"[%s] %s:%d (%s): " msg,                                               \
		level,                                                                 \
		__FILENAME__,                                                          \
		__LINE__,                                                              \
		__FUNCTION__,                                                          \
		##__VA_ARGS__                                                          \
	)
#else
#define __log_internal(...)
#endif

#define log_info(msg, ...) __log_internal("INFO", msg, ##__VA_ARGS__)
#define log_warn(msg, ...) __log_internal("WARN", msg, ##__VA_ARGS__)
#define log_error(msg, ...) __log_internal("ERROR", msg, ##__VA_ARGS__)

#endif // DEBUG_H