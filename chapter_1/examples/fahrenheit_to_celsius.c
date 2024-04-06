/*
 * ===========================================================================
 *
 *     THE C PROGRAMMING LANGUAGE (2ED) | BRIAN KERNIGHAN & DENNIS RITCHIE
 *                     Chapter 1 - A Tutorial Introduction
 *
 * 1.1 Getting Started
 *     ---------------
 *      Example: Fahrenheit to Celsius
 *
 *      °C=(5/9)(°F-32)
 *
 * ===========================================================================
 */

#include <stdio.h>

void inaccurate_fahrenheit_to_celsius(void);
void accurate_fahrenheit_to_celsius(void);
int main(void);

/**
 * print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300
 */

void inaccurate_fahrenheit_to_celsius(void)
{
	int fahr, celsius;
	int lower, upper, step;

	lower = 0;      /* lower limit of temperature scale */
	upper = 300;    /* upper limit */
	step = 20;      /* step size */

	fahr = lower;
	while (fahr <= upper) {
		celsius = 5 * (fahr-32) / 9;
		printf("%d\t%d\n", fahr, celsius);
		fahr = fahr + step;
	}
}

/**
 * print Fahrenheit-Celsius table
 * for fahr = 0, 20, ..., 300; floating-point version
 */

void accurate_fahrenheit_to_celsius(void)
{
	float fahr, celsius;
	float lower, upper, step;

	lower = 0;      /* lower limit of temperatuire scale */
	upper = 300;    /* upper limit */
	step = 20;      /* step size */

	fahr = lower;
	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%3.0f %6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
}

#if 0
{
        for fahr = 0, 20, ... , 300;

        /* floating-point version */
        float fahr, celsius;
        float lower, upper, step;

        lower = 0;      /* lower limit of temperature scale */
        upper = 300;    /* upper limit */
        step = 20;      /* step size */

        /* Celsius to Fahrenheit */
        printf("  C     F\n");
        celsius = lower;
        while (celsius <= upper) {
                fahr = 9.0*celsius / 5.0 + 32.0;
                printf("%3.0f %6.1f\n", celsius, fahr);
                celsius = celsius + step;

        /* Fahrenheit to Celsius */
        printf("  F     C\n");
        fahr = lower;
        while (fahr <= upper) {
                celsius = (5.0/9.0) * (fahr-32.0);
                printf("%3.0f %6.1f\n", fahr, celsius);
                /* printf("\e[31mbutts\n"); */
                fahr = fahr + step;
#endif

int main(void)
{
        inaccurate_fahrenheit_to_celsius();
	printf(":::\n");
	accurate_fahrenheit_to_celsius();

        return 0;
}
