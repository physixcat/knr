/*
 * ===========================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.9 Character Arrays
 *
 *      Exercise 1-17:
 *
 *      Write a program to print all input lines that are longer than 80
 *      characters.
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

#define MINLINE          80
#define MAXLINE         100

int main(void)
{
	int c, i;
	char i_eat_small_lines[MAXLINE];

	for (i=0; i < MAXLINE; ++i)
		i_eat_small_lines[i] = 0;

	i = 0;

	printf("|========o=========o=========o=========&"
	       "=========o=========o=========o=========|"
	       "\n\n");
	printf("        Input more than %d chars and I'll reprint them. "
	       "CTRL+D to exit.\n"
	       "        ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾"
	       "‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾\n"
	       "Input:\n", MINLINE);

	/*
	 * used casting ( (char)c ) to fix
	 *
	 * error: conversion from ‘int’ to ‘char’ may change value
	 * [-Werror=conversion]
	 *
	 * another solution is use less strict compiler flags
	 *
	 * also: how could I make this work with a for? hmmm
	 */
	while ((c = getchar()) != EOF) {
		if (i < MAXLINE && c != '\n')
			i_eat_small_lines[i++] = (char)c;
		if (c == '\n') {
			if (i_eat_small_lines[MINLINE]) {
				printf("Output:\n%s\n", i_eat_small_lines);
				if (i > MAXLINE-MINLINE)
					putchar('\n');
				printf("Input:\n");
			} else {
				printf("Output:\n%d more.\n\n", MINLINE-i+1);
				printf("Input:\n");
			}
			for (i=0; i < MAXLINE; ++i)
				i_eat_small_lines[i] = 0;
			i = 0;
		}
	}

	printf("\n"
	       "|========o=========o=========o=========&"
	       "=========o=========o=========o=========|"
	       "\n");

	return 0;
}
