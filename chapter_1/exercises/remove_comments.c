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
int inside_char = NO;
int just_left_comment = NO;
int line_has_code = NO;
int line_has_comment = NO;
int indentation_type = 0;
int indent_tabs = 0;
int indent_spaces = 0;

void handle_previous_slash(int c);
void process_character(int c);
void process_code(int c);
void process_non_quoted(int c);
void print_indentation(void);

int main(void)
{
	int c;

	while ((c = getchar()) != EOF) {
		process_character(c);
	}

	return 0;
}

void handle_previous_slash(int c)
{
	if (c == '*') {
		inside_comment = YES;
		line_has_comment = YES;
	} else {
		if (c != '\n' && !just_left_comment) {
			if (c_before_slash == ' ') {
/*ALERT ALERT NESTING TOO DEEP*/
				putchar(c_before_slash);
				c_before_slash = 0;
			}
			putchar(c_previous);
			c_previous = 0;
		}
	}
}

void process_character(int c)
{
	if (!inside_string && !inside_char) {
		/* handling a previous slash may change the state */
		if (c_previous == '/' && !inside_comment) {
			handle_previous_slash(c);
		}
		process_non_quoted(c);
	} else {
		putchar(c);
		line_has_code = YES;
		if (c == '\\') {
			c_before_slash = c_previous;
		}
		if (c == '\'' && (c_previous != '\\' || (c_previous == '\\' &&
                                                         c_before_slash ==
                                                         '\\'))) {
			inside_char = NO;
		}
		/* TODO: handle escaped double quote */
		if (c == '"') {
			inside_string = NO;
		}
	}

	/* don't do this for every char pls */
	if (!line_has_code) {
		if (c == '\t') {
			indent_tabs += 1;
		}
		if (c == ' ') {
			indent_spaces += 1;
		}
	}

	if (line_has_code) {
		indent_tabs = 0;
		indent_spaces = 0;
	}

	if (c == '\n') {
		line_has_code = NO;
		line_has_comment = NO;
		c_before_slash = 0;
		indent_tabs = 0;
		indent_spaces = 0;
	}

	c_previous = c;
}

void process_code(int c)
{
	if (indent_spaces || indent_tabs) {
		print_indentation();
	}

	if (line_has_code && (c_previous == ' ' || c_previous == '\t')) {
		putchar(c_previous);
		c_previous = 0;
	}

	if (c == '\'') {
		inside_char = YES;
	}

	if (c == '"') {
		inside_string = YES;
	}

	putchar(c);
	line_has_code = YES;
	just_left_comment = NO;
}

void process_non_quoted(int c)
{
	if (!inside_comment) {
		if (c == '/') {
			c_before_slash = c_previous;
		}

		if (c == '\n' && (line_has_code || !line_has_comment)) {
			putchar(c);
		}

		if (c <= ASCII_UPPER && c >= ASCII_LOWER && c != '/') {
			process_code(c);
		}

	} else {
		if (c == '/' && c_previous == '*') {
			inside_comment = NO;
			just_left_comment = YES;
			line_has_comment = YES;
			indent_spaces = 0;
		}
	}
}

void print_indentation(void)
{
	int i = 0;

	for (i = 0; i < indent_tabs; ++i) {
		putchar('\t');
	}
	for (i = 0; i < indent_spaces; ++i) {
		putchar(' ');
	}
}
