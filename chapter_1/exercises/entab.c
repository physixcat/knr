/*
 * ===========================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.10 External Variables and Scope
 *
 *      Exercise 1-21:
 *
 *      Write a program entab that replaces strings of blanks by the minimum
 *      number of tabs and blanks to achieve the same spacing. Use the same
 *      tab stops as for detab. When either a tab or a single blank would
 *      suffice to reach a tab stop, which should be given preference?
 *
 * ===========================================================================
 */

#include <stdio.h>

#define TABSTOP 8

int main (void)
{
	int c;

	int delta = TABSTOP;
	int cb = 0;

	printf("|======|=======|=======|"
	       "\n\n");

	while ((c=getchar()) != EOF) {
		if (c != ' ' && cb > 0) {
			if (delta == 8) {
				printf("%d", '\t');
				cb = 0;
			} else {
				while (cb > 0) {
					putchar(' ');
					--cb;
				}
			}
		}

		if (c != ' ' && cb == 0)
			putchar(c);

		if (c == ' ')
			++cb;

		--delta;

		if (delta == 0 || c == '\n')
			delta = TABSTOP;
	}

	return 0;
}
