/*
 * ===========================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.1 Getting Started
 *
 *      Exercise 1-02:
 *
 *      Experiment to find out what happens when prints's argument string
 *      contains \c, where c is some character not listed above.
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

int main(void)
{
	printf("I contain \t a tab\n");

	return 0;
}
