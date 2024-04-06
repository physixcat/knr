/*
 * ===========================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.7 Functions
 *     ---------------
 *      Example: Raise integer to power
 *
 * ===========================================================================
 */

#include <stdio.h>

int power(int m, int n);

/* test power function */
int main(void)
{
	int i;

	for (i = 0; i < 10; ++i)
		printf("%d %d %d\n", i, power(2,i), power(-3,i));
	return 0;
}

/* power:  raise base to n-th power; n >= 0 */
int power(int base, int n)
{
	int i,  p;

	p = 1;
	for (i = 1; i <= n; ++i)
		p = p * base;
	return p;
}
