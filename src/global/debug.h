#pragma once

#define __FILENAME__                                                           \
	(strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#ifndef NDEBUG
#define __log_internal(level, msg, ...)                                        \
	debugf(                                                                    \
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

#define log_inline(msg, ...) debugf(msg, ##__VA_ARGS__)
#define log_info(msg, ...) __log_internal("INFO", msg, ##__VA_ARGS__)
#define log_warn(msg, ...) __log_internal("WARN", msg, ##__VA_ARGS__)
#define log_error(msg, ...) __log_internal("ERROR", msg, ##__VA_ARGS__)
#define log_unimpl() __log_internal("UNIMPLEMENTED", "")

