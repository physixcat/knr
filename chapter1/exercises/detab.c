/*
 * ===========================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.10 External Variables and Scope
 *
 *      Exercise 1-20:
 *
 *      Write a program detab that replaces tabs in the input with the proper
 *      number of blanks to space to the next tab stop. Assume a fixed set of
 *      tab stops, say every n columns. Should n be a variable or a symbolic
 *      parameter?
 *
 * ===========================================================================
 */

#include <stdio.h>

#define TABSTOP 8

int main (void)
{
	int c, i;

	int delta = TABSTOP;

	printf("|======|=======|=======|"
	       "\n\n");

	while ((c=getchar()) != EOF) {
		if (c == '\t') {
			for (i=0; i < delta; ++i) {
				putchar(' ');
			}
		} else {
			putchar(c);
		}

		--delta;

		if (delta < 1 || c == '\n' || c == '\t')
			delta = TABSTOP;

	}
	printf("|======|=======|=======|"
	       "\n\n");

	return 0;
}
