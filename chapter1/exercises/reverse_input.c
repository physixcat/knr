/*
 * ===========================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.9 Character Arrays
 *
 *      Exercise 1-19:
 *
 *      Write a function reverse(s) that reverses the character string s. Use
 *      it to write a program that reverses its input a line at a time
 *
 * ===========================================================================
 */

#include <stdio.h>

void reverse(char s[], int len);

#define MAXCHAR 100

int main(void)
{
	int c, i;
	char input[MAXCHAR];

	for (i=0; i < MAXCHAR; ++i)
		input[i] = 0;

	for (i=0; i < MAXCHAR-1 && (c=getchar()) != EOF && c != '\n' ; ++i) {
		input[i] = (char)c;
	}

	reverse(input,i);
	putchar('\n');
	printf("Man from Another Place: %s\n", input);
	return 0;
}

void reverse(char s[], int len)
{
	int temp;

	int i = len-1;
	int j = 0;

	for (j=0; j < i; ++j, --i) {
		temp = s[j];
		s[j] = s[i];
		s[i] = (char)temp;
	}
}

/*
 * If compiling with -O >=2 and -Wstrict-overflow >=3 you may get this warning:
 *
 * error: assuming signed overflow does not occur when changing X +- C1 cmp C2
 * to X cmp C2 -+ C1 [-Werror=strict-overflow]
 *
 * Possible solutions:
 * - Use signed integers and range checking
 * - Use pragma macros to calm gcc (we are sure signed overflow won't happen)
 * - Lower -Wstrict-overflow to 2 or go down to -O1, -O, -O0
 */
