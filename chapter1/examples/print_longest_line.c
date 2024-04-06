/*
 * ===========================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.8 Character Arrays
 *     ---------------
 *      Example: Check which line in a group of lines is the longest
 *
 * ===========================================================================
 */

#include <stdio.h>
#define MAXLINE 10   /* maximum input line length */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line */
int main(void)
{
	int len;            /* current line length */
	int max;            /* maximum length seen so far */
	char line[MAXLINE];    /* current input line */
	char longest[MAXLINE]; /* longest line saved here */

	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}

	if (max > 0)  /* there was a line */
		printf("%s", longest);

	return 0;
}

/* getline:  read a line into s, return length  */
int getline(char s[],int lim)
{
	int c, i;

	/*
	 * used casting ( (char)c ) to fix
	 *
	 * error: conversion from ‘int’ to ‘char’ may change value
	 * [-Werror=conversion]
	 *
	 * another solution is use less strict compiler flags
	 */
	for (i=0; i < lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
		s[i] = (char)c;

	if (c == '\n') {
		s[i] = (char)c;
		++i;
	}

	s[i] = '\0';

	return i;
}

/* copy:  copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;

	i = 0;

	while ((to[i] = from[i]) != '\0')
		++i;
}
