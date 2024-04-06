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
 *      MODULO VERSION
 *
 * ===========================================================================
 */

#include <stdio.h>

int mymodulo (int columns, int tabstop);

#define TABSTOP 8

int main (void)
{
	int i = 0;
	int c;

	if (TABSTOP == 0)
		return 1;

	printf("|======|=======|=======|"
	       "\n\n");

	c = getchar();
	while (c != EOF) {
		if (c == '\t') {
			putchar(' ');
			++i;
			for (; mymodulo(i, TABSTOP) != 0; ++i)
				putchar(' ');
		} else if (c == '\n') {
			putchar('\n');
			i = 0;
		} else {
			putchar(c);
			++i;
		}

	c = getchar();
	}

	return 0;
}

int mymodulo (int columns, int tabstop)
{
	return columns - (columns / tabstop) * tabstop;
}
