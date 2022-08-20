/**
 * Cynthia Zhu
 * Professor Krzyzanowski
 * Computer Security (01:198:419:02)
 * March 6, 2022
 * 
 * Project 2, Part 2/2
 */

#define _GNU_SOURCE
#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <dlfcn.h>
#include <string.h>

int first = 1;

time_t time(time_t *tloc) {
    if (first) {
        first = 0;
        struct tm tm;
        memset(&tm, 0, sizeof(tm));
        strptime("2021-07-01 00:00:00", "%Y-%m-%d %H:%M:%S", &tm);
        tm.tm_isdst = -1;
        time_t t = mktime(&tm);
        if (tloc) {
            *tloc = t;
        }
        return t;
    } else {
        time_t (*real_time)(time_t *tloc);
        real_time = dlsym(RTLD_NEXT, "time");
        return real_time(tloc);
    }
}