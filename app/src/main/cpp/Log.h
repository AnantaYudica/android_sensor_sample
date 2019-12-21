//
// Created by Ananta Yudica on 21/12/2019.
//

#ifndef ANDROID_SENSOR_SAMPLE_LOG_H
#define ANDROID_SENSOR_SAMPLE_LOG_H

#include <android/log.h>

#define LOG(tag, format, ...)\
    __android_log_print(ANDROID_LOG_DEFAULT, tag, format __VA_ARGS__)

#define LOG_VERBOSE(tag, format, ...)\
    __android_log_print(ANDROID_LOG_VERBOSE, tag, format __VA_ARGS__)

#define LOG_DEBUG(tag, format, ...)\
    __android_log_print(ANDROID_LOG_DEBUG, tag, format __VA_ARGS__)

#define LOG_INFO(tag, format, ...) \
    __android_log_print(ANDROID_LOG_INFO, tag, format __VA_ARGS__)

#define LOG_WARN(tag, format, ...)\
    __android_log_print(ANDROID_LOG_WARN, tag, format __VA_ARGS__)

#define LOG_ERROR(tag, format, ...)\
    __android_log_print(ANDROID_LOG_ERROR, tag, format __VA_ARGS__)

#define LOG_FATAL(tag, format, ...)\
    __android_log_print(ANDROID_LOG_FATAL, tag, format __VA_ARGS__)

#define LOG_SILENT(tag, format, ...)\
    __android_log_print(ANDROID_LOG_SILENT, tag, format __VA_ARGS__)

#endif //ANDROID_SENSOR_SAMPLE_LOG_H
