/**
 * @file log.h
 * @brief Logging system with multiple severity levels
 * 
 * This header provides a flexible logging system with colored output,
 * timestamps, and multiple severity levels for debugging and monitoring
 * the simulation.
 */

#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>

/**
 * @brief Log severity levels
 * 
 * Determines the importance and filtering of log messages.
 * Lower values indicate more verbose logging.
 */
typedef enum {
    LOG_DEBUG,   /**< Detailed debugging information */
    LOG_INFO,    /**< General informational messages */
    LOG_WARN,    /**< Warning messages for potential issues */
    LOG_ERROR    /**< Error messages for serious problems */
} LogLevel;

/** @brief Global variable controlling the minimum log level to display */
extern LogLevel CURRENT_LOG_LEVEL;

/** @brief ANSI escape code to reset terminal color */
#define LOG_COLOR_RESET   "\x1b[0m"

/** @brief ANSI escape code for info messages (green) */
#define LOG_COLOR_INFO    "\x1b[32m"

/** @brief ANSI escape code for warning messages (yellow) */
#define LOG_COLOR_WARN    "\x1b[33m"

/** @brief ANSI escape code for error messages (red) */
#define LOG_COLOR_ERROR   "\x1b[31m"

/** @brief ANSI escape code for debug messages (cyan) */
#define LOG_COLOR_DEBUG    "\x1b[36m"

/**
 * @brief Log a debug message
 * 
 * Only logs if CURRENT_LOG_LEVEL is LOG_DEBUG or lower.
 * Includes file name and line number in the output.
 * 
 * @param fmt Format string (printf-style)
 * @param ... Variable arguments for format string
 */
#define log_debug(fmt, ...) \
    if (CURRENT_LOG_LEVEL <= LOG_DEBUG) log_message(LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @brief Log an informational message
 * 
 * Only logs if CURRENT_LOG_LEVEL is LOG_INFO or lower.
 * Includes file name and line number in the output.
 * 
 * @param fmt Format string (printf-style)
 * @param ... Variable arguments for format string
 */
#define log_info(fmt, ...)  \
    if (CURRENT_LOG_LEVEL <= LOG_INFO) log_message(LOG_INFO,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @brief Log a warning message
 * 
 * Only logs if CURRENT_LOG_LEVEL is LOG_WARN or lower.
 * Includes file name and line number in the output.
 * 
 * @param fmt Format string (printf-style)
 * @param ... Variable arguments for format string
 */
#define log_warn(fmt, ...)  \
    if (CURRENT_LOG_LEVEL <= LOG_WARN) log_message(LOG_WARN,  __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @brief Log an error message
 * 
 * Only logs if CURRENT_LOG_LEVEL is LOG_ERROR or lower.
 * Includes file name and line number in the output.
 * 
 * @param fmt Format string (printf-style)
 * @param ... Variable arguments for format string
 */
#define log_error(fmt, ...) \
    if (CURRENT_LOG_LEVEL <= LOG_ERROR) log_message(LOG_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

/**
 * @brief Internal function to format and output log messages
 * 
 * This function is called by the log_* macros and should not be
 * called directly. It formats the message with timestamp, severity
 * level, and source location.
 * 
 * @param level Severity level of the message
 * @param file Source file name
 * @param line Line number in source file
 * @param fmt Format string (printf-style)
 * @param ... Variable arguments for format string
 */
void log_message(LogLevel level, const char *file, int line, const char *fmt, ...);

#endif
