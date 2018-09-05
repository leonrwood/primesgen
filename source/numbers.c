#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "../headers/numbers.h"

int digitsofnumber(unsigned long long int x) {
	/*
	 * Check how many digits a number has.
	 * 
	 * */
	int n = 0;
	
	while(x != 0) {
		n++;
		x /= 10;
	}
	
	return n;
}

bool isinteger(char* str)
{
	int i = (str[0] == '-') ? 1 : 0;
	
	for(;i < strlen(str);i++) {
		if(!isdigit(str[i])) return false;
	}
	
	return true;
}

bool isintoverflow(char* num, unsigned long long int max) {
	int numlen = strlen(num);
	int maxlen = digitsofnumber(max);
	char maxnum[maxlen+1];
	
	snprintf(maxnum, maxlen+1, "%llu", max);
	
	if(numlen < maxlen) {
		return false;
	} else if(numlen > maxlen) {
		return true;
	} else if(numlen == maxlen) {
	
		for(int i = 0;i < numlen;i++) {
			if(num[i] > maxnum[i]) return true;
		}
	}
	
	return false;
}

int isprime(unsigned long long x)
{
	unsigned long long int i = 2;
	double e = sqrt(x);
	
	if(x <= 1) return false;
	if(x == 2) return true;
	
	for(;i <= e;i++) {
		if(x % i == 0) break;
	}
	
	return (i > e) ? true : false;
}
