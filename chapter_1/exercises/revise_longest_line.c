/*
 * ===========================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.9 Character Arrays
 *
 *      Exercise 1-16:
 *
 *      Revise the main routine of the longest-line program so it will
 *      correctly print the length of arbitrary long input lines, and as much
 *      as possible of the text.
 *
 * ---------------------------------------------------------------------------
 *
 * Copyright © 2024 PhysixCat
 *
 * This program is free software. It comes without any warranty, to the extent
 * permitted by applicable law. You can redistribute it and/or modify it under
 * the terms of the Do What The Fuck You Want To Public License, Version 2, as
 * published by Sam Hocevar. See the LICENSE file for more details.
 *
 * ===========================================================================
 */

#include <stdio.h>

#define MAXLINE 80

int getline(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
	int len;
	char line[MAXLINE], longest[MAXLINE];

	int max = 0;

	while ((len = getline(line, MAXLINE)) > 0) {
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	}

	if (max > 0) {
		putchar('\n');
		printf("%s\nLength: %d\n", longest, max);
	}

	return 0;
}

int getline(char s[],int lim)
{
	int c, i;

	int true_length = 0;

	/*
	 * i used casting ( (char)c ) to fix
	 *
	 * error: conversion from ‘int’ to ‘char’ may change value
	 * [-Werror=conversion]
	 *
	 * another solution is use less strict compiler flags
	 * or pragma (careful with this)
	 * #pragma GCC diagnostic push
	 * #pragma GCC diagnostic ignored "-Wconversion"
	 * -- offending code goes here --
	 * #pragma GCC diagnostic pop
	 */

	for (i=0; (c=getchar())!=EOF && c!='\n'; ++i) {
		++true_length;
		if (i < lim-1)
			s[i] = (char)c;
	}

	if (i < lim-1 && c == '\n') {
		s[i] = (char)c;
		++i;
	}

	s[lim] = '\0';

	return true_length;
}

void copy(char to[], char from[])
{
	int i = 0;

	while ((to[i] = from[i]) != '\0')
		++i;
}

/*
 * If compiling with -O >=2 and -Wstrict-overflow >=3 you may get this warning:
 *
 * error: assuming signed overflow does not occur when changing X +- C1 cmp C2
 * to X cmp C2 -+ C1 [-Werror=strict-overflow]
 *
 * Possible solutions:
 * - Use signed integers and range checking
 * - Use pragma macros to calm gcc (we are sure signed overflow won't happen)
 * - Lower -Wstrict-overflow to 2 or go down to -O1, -O, -O0
 */
