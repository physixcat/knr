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
