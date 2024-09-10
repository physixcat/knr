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

#define CHARACTER_LIMIT 100
#define NO 0
#define YES 1

void array_set(char array[], int count);
void blank_print(char blank_sequence[CHARACTER_LIMIT], int blank_index);

int main(void)
{
	char blank_sequence[CHARACTER_LIMIT] = "";
	char line_buffer[CHARACTER_LIMIT] = "";
	char word[CHARACTER_LIMIT] = "";
	int blank_index = 0;
	int line_has_code = NO;
	int multiline_detected = NO;

	int c;
	int i = 0;
	int inside_comment = NO;
	int inside_string = NO;
	int quiet_risk = NO;
	int yapping_risk = NO;
	int escaping_character = NO;

	while ((c = getchar()) != EOF) {
		if (c == '/' && !inside_comment) {
			yapping_risk = YES;
		}
		if (c == '*' && yapping_risk) {
			inside_comment = YES;
			yapping_risk = NO;
		} else if (c == '*') {
			yapping_risk = NO;
		}
		if (c == '*' && inside_comment) {
			quiet_risk = YES;
		}
		if (c == '/' && quiet_risk) {
			inside_comment = NO;
			quiet_risk = NO;
		} else if (c == '/') {
			quiet_risk = NO;
		}
		if (c == '"' && !escaping_character && !inside_string && !inside_comment) {
			inside_string = YES;
		}
		if (c == '\\' && inside_string) {
			inside_string = NO;
		}
		if (c == '\n') {
		}
		line_buffer[i] = c;
		++i;
	}

	return 0;
}

void array_set(char array[], int count)
{
	int i;

	for (i = 0; i < count; ++i) {
		array[i] = 0;
	}
}

void blank_print(char blank_sequence[CHARACTER_LIMIT], int blank_index)
{
	int i;

	for (i = 0; i < blank_index; ++i) {
		if (blank_sequence[i] == '\t') {
			putchar('\t');
		}
		if (blank_sequence[i] == ' ') {
			putchar(' ');
		}
	}
}
