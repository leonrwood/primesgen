/******************************************************************************
 * PROGRAM NAME : primesgen
 * PURPOSE : To Generate primes in the given range
 * PARAMETER : primesgen <min> <max> (min and max need to be positive integers)
 * VERSION : 1.0
 * AUTHOR: Leon R. Wood
 * LAST MODIFIED: Sep. 4th, 2018
 ******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <time.h>

#ifdef WINDOWS
    #include <direct.h>
    #define getcurrentdir _getcwd
#else
    #include <unistd.h>
    #define getcurrentdir getcwd
#endif
 
#include "../headers/numbers.h"
#include "../headers/files.h"

#define FILENAME "/primes"
#define APPNAME "primesgen"
#define AUTHOR "Leon.r.Wood"
#define EMAIL "leon.r.wood@qq.com"
#define DATE "Sep. 4th, 2018"
#define VERSION "1.0"

void help()
{
	char* appname = APPNAME;
	printf("\t\t---------------HELP---------------\n");
	printf("Name: \t\t[%s]\n", appname);
	printf("Author: \tCreated by Leon R. Wood.\n");
	printf("Usage: \t\tfind out all the prime numbers in the given range.\n");
	printf("Example 1: \t[%s 1 100] prints out prime numbers between 1 and 100.\n", appname);
	printf("Example 2: \t[%s 23] tells whether 23 is a prime number.\n", appname);
	printf("-h, --help \tprint out this help page.\n");
	printf("-v, --version \tprint out version page.\n");
	printf("\t\tNeed more help, please contact the author at ");
	printf(EMAIL);
	printf("\n");
}

void version()
{
	char* version = VERSION;
	char* author = AUTHOR;
	char* date = DATE;
	
	printf("\t\t---------------Version %s---------------\n", version);
	printf("Author: %s\n", author);
	printf("Compiled on %s\n", date);
}

void error()
{
	printf("\t\t---------------Error---------------\n");
	printf("Please make sure your arguments are correct.\n");
	printf("The maximum possible number is: \n");
	printf("%llu\n", ULONG_LONG_MAX);
	printf("The lower bound and upper bound should only be positive.\n");
}

int resultprint(unsigned long n, unsigned long long x, 
				 int cols, bool showlinenumber, bool output, char* path)
{
	return 0;
}

void errormsg(char* msg)
{
	printf("%s\n", msg);
}

int main(int argc, char* argv[]) {
	
	unsigned long long int x = 0;
	unsigned long long int min = 0;
	unsigned long long int max = 0;
	unsigned long int n = 0;
	int cols = 1;
	bool output = false;
	bool showlinenumber = false;
	bool datetimesuffix = false;
	char path[FILENAME_MAX];
	FILE* f;
	
	switch (argc) {
		case 1:
			help();
			break;
		case 2:
			if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
				help();
			} else if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
				version();
			} else if (isinteger(argv[1]) && !isintoverflow(argv[1], ULONG_LONG_MAX)) {
				if(isprime(atoi(argv[1])))
					printf("%llu is a prime number.\n", (long long int)atoi(argv[1]));
				else
					printf("%llu is not a prime number.\n", (long long int)atoi(argv[1]));
			} else {
				error();
			}
			break;
		default:
			if(argv[1][0] == '-' || argv[2][0] == '-'
								 || !isinteger(argv[1]) 
								 || !isinteger(argv[2])) {
				error();
				return 1;
			} else if(isintoverflow(argv[1], ULONG_LONG_MAX) || 
					  isintoverflow(argv[2], ULONG_LONG_MAX) ) {
				error();
				return 1;
			}

			for(int i = 3;i < argc;i++) {
				if ((strcmp(argv[i],"-o") == 0 || 
					strcmp(argv[i],"--output") == 0)
					&& !output) {
					output = true;
					
					if (i < argc-1 && argv[i+1][0] != '-') {
						if(ispathexists(argv[i+1])) {
							strcpy(path, argv[i+1]);

							if(path[strlen(path)-1] == '/' ||
							   path[strlen(path)-1] == '\\') {
								path[strlen(path)-1] = '\0';
							}
							
							i++;
						} else {
							errormsg(strcat(argv[i+1], " doesn't exist or is not accessible."));
							return 1;
						}
					} else {
						if(!getcurrentdir(path, sizeof(path))) {
							error();
						return 1;
						} else {
							path[sizeof(path) - 1] ='\0';
						}					
					}
				
				} else if ((strcmp(argv[i],"-s") == 0 || 
						   strcmp(argv[i],"--showlinenumber") == 0)
						   && !showlinenumber) {
					showlinenumber = true;
				} else if ((strcmp(argv[i],"-d") == 0 || 
						   strcmp(argv[i],"--datetime") == 0)
						   && !datetimesuffix) {
					datetimesuffix = true;
				}
			}

			if(output) {
				if(datetimesuffix) {
					time_t t = time(NULL);
					struct tm tm = *localtime(&t);
					char timestr[15];
					
					snprintf(timestr, sizeof(timestr) , "/primes%d%d%d%d%d%d", 
							 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, 
							 tm.tm_hour, tm.tm_min, tm.tm_sec);
							 
					strcat(path, timestr);
				} else {
					strcat(path, FILENAME);
				}
				
				if(isfileexists(path)) f = fopen(path, "a");
				else f = fopen(path, "w");
				
				if(f == NULL) {
					printf("%s\n", path);
					errormsg("Primes.txt cannot be created in the directory.");
					return 1;
				}
			}
			
			min = atoi(argv[1]);
			max = atoi(argv[2]);
			
			for(x = min;x <= max;x++){
				if(isprime(x)) {
					n++;
					
					if(!output) {
						if (showlinenumber && cols == 1) printf("%lu:%llu\n", n, x);
						if (showlinenumber && cols != 1) {
							printf("%lu:%llu\t\t", n, x);
							if(n % cols == 0) printf("\n");
						}
						if(!showlinenumber && cols == 1) printf("%llu\n", x);
						if(!showlinenumber && cols !=1) {
							printf("%llu\t\t", x);
							if(n % cols == 0) printf("\n");
						}
					} else {
						if (showlinenumber && cols == 1) fprintf(f, "%lu:%llu\n", n, x);
						if (showlinenumber && cols != 1) {
							fprintf(f, "%lu:%llu\t\t", n, x);
							if(n % cols == 0) printf("\n");
						}
						if(!showlinenumber && cols == 1) fprintf(f, "%llu\n", x);
						if(!showlinenumber && cols !=1) {
							fprintf(f, "%llu\t\t", x);
							if(n % cols == 0) printf("\n");
						}
					}
				}
			}
			
			if (n == 0) errormsg("No Primes Found!");
			else printf("\n\n\t\tFinally, %lu prime numbers are found!\n", n);

			break;
	}
	
	if(output) fclose(f);
	
	return 0;
}
