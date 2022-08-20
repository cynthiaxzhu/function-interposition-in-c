/**
 * Cynthia Zhu
 * Professor Krzyzanowski
 * Computer Security (01:198:419:02)
 * March 6, 2022
 * 
 * Project 2, Part 1/2
 */

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <dirent.h>
#include <dlfcn.h>
#include <string.h>

bool hide(char* result_name) {
    char* HIDDEN_value = getenv("HIDDEN");
    char hide_names[500];
    strcpy(hide_names, HIDDEN_value);
    char* hide_name = strtok(hide_names, ":");
    while (hide_name) {
        if (strcmp(result_name, hide_name) == 0) {
            return true;
        }
        hide_name = strtok(NULL, ":");
    }
    return false;
}

struct dirent* readdir(DIR* dirp) {
    struct dirent* (*real_readdir)(DIR* dirp);
    real_readdir = dlsym(RTLD_NEXT, "readdir");
    struct dirent* result = real_readdir(dirp);
    while (result && hide(result->d_name)) {
        result = real_readdir(dirp);
    }
    return result;
}