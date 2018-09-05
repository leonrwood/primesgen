#include "../headers/files.h"

bool ispathexists(char* path)
{
	DIR* dir = opendir(path);
	
	if(dir) {
		closedir(dir);
	} else if (ENOENT == errno) {
		return false;
	} else {
		return false;
	}
	
	return true;
}

bool isfileexists(char* filepath)
{
	return false;
}
