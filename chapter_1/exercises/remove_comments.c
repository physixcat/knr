/*
 * ============================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.?? Final exercises
 *      ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *      Exercise 1-23:
 *
 *      Write a program to remove all comments from a C program.  Don't forget
 *      to handle quoted strings and character constants properly. C comments
 *      don't nest.
 *
 * ----------------------------------------------------------------------------
 *
 * Copyright © 2024 PhysixCat
 *
 * This program is free software. It comes without any warranty, to the extent
 * permitted by applicable law. You can redistribute it and/or modify it under
 * the terms of the Do What The Fuck You Want To Public License, Version 2, as
 * published by Sam Hocevar. See the LICENSE file for more details.
 *
 * ============================================================================
 */

#include <stdio.h>

#define ASCII_EXT_LOWER 128
#define ASCII_LOWER     33
#define ASCII_UPPER     126
#define NO              0
#define YES             1

int c_previous = 0;
int c_before_slash = 0;
int inside_comment = NO;
int inside_string = NO;
int line_has_code = NO;
int line_has_comment = NO;

void process_character(int c);
void process_code(int c);
void process_non_string(int c);

int main(void)
{
	int c;

	while ((c = getchar()) != EOF) {
		process_character(c);
	}

	return 0;
}

void process_character(int c)
{
	if (!inside_string) {
		process_non_string(c);
	} else {
		putchar(c);
		line_has_code = YES;

		if (c == '"') {
			inside_string = NO;
		}
	}

	if (c == '\n') {
		line_has_code = NO;
		line_has_comment = NO;
	}

	c_previous = c;
}

void process_non_string(int c)
{
	if (!inside_comment) {
		if (c_previous == '/' && c != '\n' && c != '*') {
			/* printf("$"); */
			if (c_before_slash == ' ') {
				putchar(c_before_slash);
			}
			putchar(c_previous);
		}

		if (c == '/') {
			/* printf("^"); */
			c_before_slash = c_previous;
		} else if (c == '*' && c_previous == '/') {
			inside_comment = YES;
		} else if (c == '\n' && (line_has_code || !line_has_comment)) {
			/* printf("%%"); */
			putchar(c);
		} else if (c <= ASCII_UPPER && c >= ASCII_LOWER) {
			/* printf("&"); */
			process_code(c);
		}
	} else {
		if (c == '/' && c_previous == '*') {
			/* printf("#"); */
			inside_comment = NO;
			line_has_comment = YES;
		}
	}
}

void process_code(int c)
{
	if (c_previous == ' ' || c_previous == '\t') {
		/* printf("!"); */
		putchar(c_previous);
	}

	if (c == '"') {
		inside_string = YES;
	}

	/* printf("?"); */
	putchar(c);
	line_has_code = YES;
}
