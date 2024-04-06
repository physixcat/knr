/*
 * ===========================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.10 External Variables and Scope
 *
 *      Example: longest line program with external variables
 *
 * ===========================================================================
 */

#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int max;                /* maximum length seen so far */
char line[MAXLINE];     /* current input line */
char longest[MAXLINE];  /* longest line saved here */

int getline(void);
void copy(void);

/* print longest input line; specialized version */
int main(void)
{
	int len;
	extern int max;
	extern char longest[];

	max = 0;
	while ((len = getline()) > 0)
		if (len > max) {
			max = len;
			copy();
		}
	if (max > 0)  /* there was a line */
		printf("%s", longest);
	return 0;
}

/* getline:  specialized version */
int getline(void)
{
	int c, i;
	extern char line[];

	for (i = 0; i < MAXLINE - 1
		&& (c=getchar()) != EOF && c != '\n'; ++i)
			line[i] = (char)c;
	if (c == '\n') {
		line[i] = (char)c;
		++i;
	}
	line[i] = '\0';
	return i;
}

/* copy: specialized version */
void copy(void)
{
	int i;
	extern char line[], longest[];

	i = 0;
	while ((longest[i] = line[i]) != '\0')
                ++i;
}
