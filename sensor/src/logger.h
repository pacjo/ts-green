#pragma once

#include <Arduino.h>

// -- log levels --------------------------------------------------------------
enum {
    LOG_LEVEL_DEBUG = 0,
    LOG_LEVEL_INFO  = 1,
    LOG_LEVEL_WARN  = 2,
    LOG_LEVEL_ERROR = 3,
};

// compile-time filter – set to LOG_LEVEL_DEBUG for verbose output
#ifndef LOG_LEVEL
#define LOG_LEVEL  LOG_LEVEL_INFO
#endif

// -- core macro --------------------------------------------------------------
#if LOG_LEVEL <= LOG_LEVEL_DEBUG
#define LOG_DEBUG(tag, fmt, ...)  Serial.printf("[%6lu][D][%s] " fmt "\n", millis(), tag, ##__VA_ARGS__)
#else
#define LOG_DEBUG(tag, fmt, ...)  ((void)0)
#endif

#if LOG_LEVEL <= LOG_LEVEL_INFO
#define LOG_INFO(tag, fmt, ...)   Serial.printf("[%6lu][I][%s] " fmt "\n", millis(), tag, ##__VA_ARGS__)
#else
#define LOG_INFO(tag, fmt, ...)   ((void)0)
#endif

#if LOG_LEVEL <= LOG_LEVEL_WARN
#define LOG_WARN(tag, fmt, ...)   Serial.printf("[%6lu][W][%s] " fmt "\n", millis(), tag, ##__VA_ARGS__)
#else
#define LOG_WARN(tag, fmt, ...)   ((void)0)
#endif

#if LOG_LEVEL <= LOG_LEVEL_ERROR
#define LOG_ERROR(tag, fmt, ...)  Serial.printf("[%6lu][E][%s] " fmt "\n", millis(), tag, ##__VA_ARGS__)
#else
#define LOG_ERROR(tag, fmt, ...)  ((void)0)
#endif
