#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
//#include <sys/types.h>
#include <stdbool.h>

#ifndef LEON_FILES
#define LEON_FILES

bool ispathexists(char* path);
bool isfileexists(char* filepath);

#endif
