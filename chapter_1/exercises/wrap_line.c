/*
 * ============================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.?? Final exercises
 *      ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
 *      Exercise 1-22:
 *
 *      Write a program to "fold" long input lines into two or more shorter
 *      lines after the last non-blank character that occurs before the n-th
 *      column of input. Make sure your program does something intelligent
 *      with very long lines, and if there are no blanks or tabs before the
 *      specified column.
 *
 * Notes:
 *
 * This program takes text from standard input. The user can change the desired
 * format of the output from the compile-time options. However, this is very
 * inconvenient, and is supported to strictly use only what has been seen so
 * far in the book. The option to enable command line argument support is
 * there; I strongly recommend turning it on. It is also possible to bake in an
 * input string for testing purposes.
 *
 * In contrast to UNIX's fold, this line wrapper defaults to line breaking when
 * a word doesn't fit on a line. It also implements the use of dashes to break
 * up words that are too big. If prefering dashes is enabled, the program will
 * attempt to preserve as many of the original text's leading blanks as
 * possible. Otherwise, it will prioritize avoiding word splits over them.
 * Trailing blanks are never printed. Leading blanks are only printed if a word
 * will be on the line and there's room for them.
 *
 * The minimum width for output is 2 columns. This is so that we can guarantee
 * room for a dash.
 *
 * If enabled, valid command line arguments are:
 * -w #, where # is the desired width of the output in columns.
 * -v, for verbose output.
 * -d, for prefering dashes in the output
 * Example: ./bin_wrap_line -w 16 -d -v
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
#define COLUMN_MIN      2
#define LONGEST_WORD    34
#define NO              0
#define STRING_BAKED_IN NO
#define TAB_STOP        8
#define YES             1
/*
 * Compile-time options. I strongly recommend leaving these alone and simply
 * enabling command line arguments below to improve usability.
 */
#define COLUMN_MAX      80
#define PREFER_DASHES   NO
#define PREFER_VERBOSE  NO
/*
 * This is the cheat toggle. Command line arguments make using the program
 * easier, but here they break my rule of using things from later chapters. To
 * turn them on, change NO to YES.
 */
#define CLI_ARGUMENTS_ENABLED NO

/*
 * I need to modify these variables in many functions, but I can't use pointers
 * yet because this is chapter 1. Therefore, I use two external variables.
 */
int column = 0;
int letter = 0;

int tab_get_distance(void);
void array_set(char array[], int count);
void blank_print(char blank_sequence[COLUMN_MAX], int blank_index);
void line_break_if_needed(int line_has_word, int column_width);
void line_set_if_needed(int blank_index);
void word_decide_printing_style(char blank_sequence[COLUMN_MAX], char word [LONGEST_WORD],
                                int blank_index, int column_width, int line_has_word,
                                int prefer_dashes);
void word_print_wide(char blank_sequence[COLUMN_MAX], char word[LONGEST_WORD], int blank_index,
                     int column_width, int line_has_word);
void word_split(char word[LONGEST_WORD], int column_width, int column_original);

#if CLI_ARGUMENTS_ENABLED
int main(int argc, char **argv)
#else
int main(void)
#endif
{
	int blank_index = 0;
	char blank_sequence[COLUMN_MAX] = "";
	/*
	 * If !CLI_ARGUMENTS_ENABLED, it would be nice to get rid of the
	 * column_width, prefer_dashes, and prefer_verbose variables; then I'd
	 * just use the symbolic constants COLUMN_MAX, PREFER_DASHES, and
	 * PREFER_VERBOSE. However, that would require all calls to have a
	 * separate version; we also can't use const yet because this is
	 * chapter 1... too bad!
	 */
	int column_width = COLUMN_MAX;
	int inside_word = NO;
	int line_has_word = NO;
	int prefer_dashes = PREFER_DASHES;
	int forced_new_line = NO;
	int prefer_verbose = PREFER_VERBOSE;
	char word[LONGEST_WORD] = "";
#if STRING_BAKED_IN
	unsigned char c[] = "\tLorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
	                    "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim "
	                    "ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
	                    "aliquip ex ea commodo consequat. Duis aute irure dolor in "
	                    "reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
	                    "pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
	                    "culpa qui officia deserunt mollit anim id est laborum.\n";
#else
	int c;
#endif
#if STRING_BAKED_IN || CLI_ARGUMENTS_ENABLED
	int i;
#endif

#if CLI_ARGUMENTS_ENABLED
	for (i = 1; i < argc; ++i) {
		if (argv[i][0] == '-' && argv[i][1] == 'd' && argv[i][2] == '\0') {
			prefer_dashes = YES;
		}
		if (argv[i][0] == '-' && argv[i][1] == 'w' && argv[i][2] == '\0' && i + 1 < argc) {
			sscanf(argv[i+1], "%d", &column_width);
		}
		if (argv[i][0] == '-' && argv[i][1] == 'v' && argv[i][2] == '\0') {
			prefer_verbose = YES;
		}
	}
#endif
	if (column_width < 2) {
		printf("Error: width cannot be lower than %d. Bailing out.\n", COLUMN_MIN);
		return 1;
	}
	if (column_width > COLUMN_MAX) {
		printf("Error: width cannot be higher than %d. Bailing out.\n", COLUMN_MAX);
		return 1;
	}
	if (prefer_verbose) {
		printf("Width: %d\n", column_width);
		if (prefer_dashes) {
			printf("Prefering dashes.\n");
		} else {
			printf("Avoiding dashes when possible.\n");
		}
#if STRING_BAKED_IN
		printf("Test string: \"%s\"\n\n", c);
#endif
		printf("           +8      +8      +8      +8      +8      +8      +8      "
		       "+8      +8\n");
		printf("012345678=======16======24======32======40======48======56======64======"
		       "72======80\n");
	}

#if STRING_BAKED_IN
	#define ARRAY_SIZE(x)   (sizeof(x) / sizeof((x)[0]))
	for (i = 0; i < (int)ARRAY_SIZE(c); ++i) {
		if (c[i] >= ASCII_LOWER && c[i] <= ASCII_UPPER && letter < LONGEST_WORD) {
			word[letter] = (char)c[i];
#else
	while ((c = getchar()) != EOF) {
		if (c >= ASCII_LOWER && c <= ASCII_UPPER && letter < LONGEST_WORD) {
			word[letter] = (char)c;
#endif
			++letter;
			++column;
			inside_word = YES;
		} else if (letter >= LONGEST_WORD) {
			printf("Error: single word cannot be longer than %d characters. "
			"Bailing out.\n", LONGEST_WORD);
			return 1;
#if STRING_BAKED_IN
		} else if (c[i] >= ASCII_EXT_LOWER) {
#else
		} else if (c >= ASCII_EXT_LOWER) {
#endif
			printf("Error: extended ASCII is not supported. Bailing out.\n");
			return 1;
		} else {
			inside_word = NO;
		}
		if (!inside_word && letter) {
			forced_new_line = NO;
			word_decide_printing_style(blank_sequence, word, blank_index, column_width,
			                           line_has_word, prefer_dashes);
			array_set(word, letter);
			array_set(blank_sequence, blank_index);
			blank_index = 0;
			letter = 0;
			line_has_word = YES;
		}
#if STRING_BAKED_IN
		if (c[i] == ' ' && blank_index < COLUMN_MAX && column && !forced_new_line) {
			blank_sequence[blank_index] = (char)c[i];
#else
		if (c == ' ' && blank_index < COLUMN_MAX && column && !forced_new_line) {
			blank_sequence[blank_index] = (char)c;
#endif
			++blank_index;
			++column;
		}
#if STRING_BAKED_IN
		if (c[i] == '\t' && blank_index < COLUMN_MAX && column_width > TAB_STOP &&
		    column < column_width - TAB_STOP) {
			blank_sequence[blank_index] = (char)c[i];
#else
		if (c == '\t' && blank_index < COLUMN_MAX && column_width > TAB_STOP &&
		    column < column_width - TAB_STOP) {
			blank_sequence[blank_index] = (char)c;
#endif
			++blank_index;
			column += tab_get_distance();
#if STRING_BAKED_IN
		} else if (c[i] == '\t' && blank_index < COLUMN_MAX && column_width > TAB_STOP &&
		    column >= column_width - TAB_STOP && line_has_word) {
#else
		} else if (c == '\t' && blank_index < COLUMN_MAX && column_width > TAB_STOP &&
		    column >= column_width - TAB_STOP && line_has_word) {
#endif
			array_set(blank_sequence, blank_index);
			blank_index = 0;
			column = 0;
			putchar('\n');
			line_has_word = NO;
			forced_new_line = YES;
		}
#if STRING_BAKED_IN
		if (c[i] == '\n') {
#else
		if (c == '\n') {
#endif
			array_set(blank_sequence, blank_index);
			blank_index = 0;
			column = 0;
			putchar('\n');
			line_has_word = NO;
			forced_new_line = NO;
		}
	}
	if (letter) {
		word_decide_printing_style(blank_sequence, word, blank_index, column_width,
		                           line_has_word, prefer_dashes);
	}
	if (prefer_verbose) {
		printf("012345678=======16======24======32======40======48======56======64======"
		       "72======80\n");
		printf("           +8      +8      +8      +8      +8      +8      +8      "
		       "+8      +8\n\n");
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

void blank_print(char blank_sequence[COLUMN_MAX], int blank_index)
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

void line_break_if_needed(int line_has_word, int column_width)
{
	if (line_has_word) {
		if (letter <= column_width) {
			column = letter;
		}
		putchar('\n');
	}
}

void line_set_if_needed(int blank_index)
{
	if (blank_index) {
		column = letter;
	}
}

int tab_get_distance(void)
{
	return (TAB_STOP - (column - TAB_STOP * (column / TAB_STOP)));
}

void word_decide_printing_style(char blank_sequence[COLUMN_MAX], char word [LONGEST_WORD],
                                int blank_index, int column_width, int line_has_word,
                                int prefer_dashes)
{
#if !STRING_BAKED_IN
	word[letter] = '\0';
#endif
	if (column <= column_width) {
		if (blank_index) {
			blank_print(blank_sequence, blank_index);
		}
		printf("%s", word);
	} else {
		if (letter <= column_width && !prefer_dashes) {
			line_break_if_needed(line_has_word, column_width);
			line_set_if_needed(blank_index);
			printf("%s", word);
		} else {
			word_print_wide(blank_sequence, word, blank_index, column_width,
			                line_has_word);
		}
	}
}

void word_print_wide(char blank_sequence[COLUMN_MAX], char word[LONGEST_WORD], int blank_index,
                     int column_width, int line_has_word)
{
	int column_original = column;

	if (column - letter >= column_width - 1) {
		line_break_if_needed(line_has_word, column_width);
		line_set_if_needed(blank_index);
	} else if (blank_index) {
		blank_print(blank_sequence, blank_index);
	}
	if (column_original <= column_width || (letter <= column_width && column == letter)) {
		printf("%s", word);
	} else {
		word_split(word, column_width, column_original);
	}
}

void word_split(char word[LONGEST_WORD], int column_width, int column_original)
{
	int i = 0;
	int j = 0;
	int column_shift = column_original - letter;
	int column_width_temp = column_width;

	if (column_shift + 1 < column_width) {
		column_width_temp -= column_shift;
	}
	while (column_shift < column_original) {
		while (i < column_width_temp + j - 1 && i < letter - 1) {
			putchar(word[i]);
			++i;
			++column;
			++column_shift;
		}
		j = i;
		if (column_shift + 1 < column_original) {
			putchar('-');
			column = 1;
			putchar('\n');
			column_width_temp = column_width;
		} else {
			putchar(word[i]);
			++column_shift;
		}
	}
}
