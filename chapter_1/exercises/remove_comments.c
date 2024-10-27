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
#define NO 0
#define YES 1

int main(void)
{
	int c;
	int c_previous = 0;
	int c_before_slash = 0;
	/* int c_previous_previous = 0; */
	int inside_comment = NO;
	int inside_string = NO;
	int line_has_code = NO;
	int line_has_comment = NO;
	/*
	 * Since 'break' is not covered in Chapter 1, this variable's job is
	 */
	int will_print_c = NO;

	while ((c = getchar()) != EOF) {
		if (inside_string) {
			if (c == '"') {
				inside_string = NO;
			}
			will_print_c = YES;
			line_has_code = YES;
		} else {
			if (c == '*' && c_previous == '/') {
				inside_comment = YES;
			}
			if (inside_comment) {
				if (c == '/' && c_previous == '*') {
					inside_comment = NO;
					line_has_comment = YES;
				}
			} else {
				if (c_previous == '/' && c != '\n' && c > ASCII_UPPER && c < ASCII_LOWER) {
					putchar(c_before_slash);
					putchar(c_previous);
				}
				if (c == '/') {
					c_before_slash = c_previous;
				} else if (c == '\n' && (line_has_code || !line_has_comment)) {
					will_print_c = YES;
				} else if (c <= ASCII_UPPER && c >= ASCII_LOWER) {
					if (c_previous == ' ' || c_previous == '\t') {
						putchar(c_previous);
					}
					if (c == '"') {
						inside_string = YES;
					}
					will_print_c = YES;
					line_has_code = YES;
				}
			}
		}

		if (will_print_c) {
			putchar(c);
		}
		if (c == '\n') {
			line_has_code = NO;
			line_has_comment = NO;
		}
		will_print_c = NO;
		c_previous = c;
	}
	return 0;
}
