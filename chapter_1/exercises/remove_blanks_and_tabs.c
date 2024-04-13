/*
 * ===========================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.9 Character Arrays
 *
 *      Exercise 1-18:
 *
 *      Write a program to remove trailing blanks and tabs from each line of
 *      input, and to delete entirely blank lines.
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

#define MAXCHAR         1024

int main(void)
{
	int c, i;
	char output[MAXCHAR];

	int oldc = 0;

	for (i=0; i < MAXCHAR; ++i)
		output[i] = 0;

	for (i=0; (i < MAXCHAR) && (c=getchar()) != EOF; ++i) {
		if (c==' ' || c=='\t') {
			--i;
		} else if (oldc == '\n' && c == '\n') {
			--i;
		} else {
			output[i] = (char)c;
			oldc = (char)c;
		}
	}

	putchar('\n');
	printf("Output:\n%s", output);

	return 0;
}
