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

int c_before_slash = 0;
int c_previous = 0;
int inside_char = NO;
int inside_string = NO;
int just_left_comment = NO;
int line_has_code = NO;

void process_non_comment(int c, int line_has_comment, int indent_tabs, int indent_spaces);

int main(void)
{
	int c;
	int indent_spaces = 0;
	int indent_tabs = 0;
	int inside_comment = NO;
	int line_has_comment = NO;

	while ((c = getchar()) != EOF) {
		if (!inside_string && !inside_char) {
			if (!inside_comment) {
				if (c_previous == '/') {
					if (c == '*') {
						inside_comment = YES;
						line_has_comment = YES;
					} else {
						if (c != '\n' && !just_left_comment) {
							if (c_before_slash == ' ') {
								putchar(c_before_slash);
								c_before_slash = 0;
							}
							putchar(c_previous);
							c_previous = 0;
						}
						process_non_comment(c, line_has_comment,
						                    indent_tabs, indent_spaces);
					}
				} else {
					process_non_comment(c, line_has_comment, indent_tabs,
					                    indent_spaces);
				}
			} else if (c == '/' && c_previous == '*') {
				inside_comment = NO;
				just_left_comment = YES;
				line_has_comment = YES;
				indent_spaces = 0;
			}
		} else {
			putchar(c);
			line_has_code = YES;
			if (c == '\\') {
				c_before_slash = c_previous;
			} else if (c == '\'' && (c_previous != '\\' || (c_previous == '\\' &&
			                                         c_before_slash == '\\'))) {
				inside_char = NO;
			} else if (c == '"' && c_previous != '\\') {
				inside_string = NO;
			}
		}

		if (!line_has_code) {
			if (c == '\t') {
				indent_tabs += 1;
			}
			if (c == ' ') {
				indent_spaces += 1;
			}
		}

		if (c == '\n') {
			line_has_code = NO;
			if (!inside_comment) {
				line_has_comment = NO;
			}
			c_before_slash = 0;
			indent_tabs = 0;
			indent_spaces = 0;
		}

		c_previous = c;
	}

	return 0;
}

void process_non_comment(int c, int line_has_comment, int indent_tabs, int indent_spaces)
{
	int i = 0;

	if (c == '/') {
		c_before_slash = c_previous;
	} else if (c == '\n' && (line_has_code || !line_has_comment)) {
		putchar(c);
	} else if (c <= ASCII_UPPER && c >= ASCII_LOWER && c != '/') {
		if ((indent_spaces || indent_tabs) && !line_has_code) {
			for (i = 0; i < indent_tabs; ++i) {
				putchar('\t');
			}
			for (i = 0; i < indent_spaces; ++i) {
				putchar(' ');
			}
		}

		if (line_has_code && (c_previous == ' ' || c_previous == '\t')) {
			putchar(c_previous);
			c_previous = 0;
		}

		if (c == '\'') {
			inside_char = YES;
		} else if (c == '"') {
			inside_string = YES;
		}

		putchar(c);
		line_has_code = YES;
		just_left_comment = NO;
	}
}
