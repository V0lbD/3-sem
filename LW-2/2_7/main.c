#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

typedef struct Coordinates_of_point
{
	double x, y;
} Ñoordinates_of_point;

typedef struct Coordinates_of_vector
{
	double x, y;
} Ñoordinates_of_vector;

Ñoordinates_of_vector vect(Ñoordinates_of_point p1, Ñoordinates_of_point p2)
{
	Ñoordinates_of_vector vect;

	vect.x = p2.x - p1.x;
	vect.y = p2.y - p1.y;

	return vect;
}

double skew_product(Ñoordinates_of_vector vect1, Ñoordinates_of_vector vect2)
{
	return vect1.x * vect2.y - vect2.x * vect1.y;
}

int is_convex(int n, ...)
{
	int i = 0, flag = 1;
	Ñoordinates_of_point p1, p2, p3, first, second;
	Ñoordinates_of_vector vect1, vect2;

	va_list factor;
	va_start(factor, n);

	p1 = va_arg(factor, Ñoordinates_of_point);
	first = p1;
	p2 = va_arg(factor, Ñoordinates_of_point);
	second = p2;
	p3 = va_arg(factor, Ñoordinates_of_point);

	vect1 = vect(p1, p2);
	vect2 = vect(p2, p3);

	for (i = 3; i < n; i++) {
		if (skew_product(vect1, vect2) > 0) {
			p1 = p2;
			p2 = p3;
			p3 = va_arg(factor, Ñoordinates_of_point);

			vect1 = vect(p1, p2);
			vect2 = vect(p2, p3);
		}
		else {
			flag = 0;
			break;
		}
	}
	va_end(factor);

	if (skew_product(vect1, vect2) >= 0) {
		p1 = p2;
		p2 = p3;
		p3 = first;

		vect1 = vect(p1, p2);
		vect2 = vect(p2, p3);
	}
	else {
		flag = 0;
	}

	if (skew_product(vect1, vect2) >= 0) {
		p1 = p2;
		p2 = p3;
		p3 = second;
		vect1 = vect(p1, p2);
		vect2 = vect(p2, p3);
	}
	else {
		flag = 0;
	}

	if (skew_product(vect1, vect2) >= 0) {
	}
	else {
		flag = 0;
	}

	return flag;
}

double polynomial(double x, int n, ...)
{
	int i = 0;

	va_list factor;
	va_start(factor, n + 1);

	double result = va_arg(factor, double);

	for (i = 0; i < n; i++) {
		// *(arr + i) = va_arg(factor, double);
		result = result * x + va_arg(factor, double);
	}

	return result;
}

int main()
{
	int choice = 0;
	printf("If you want to find out if the polygon is convex, enter 1\n");
	printf("If you want to find the value of the polynomial at a given point, enter 2\n");
	if (scanf("%d", &choice) != 1) {
		printf("You have entered something wrong!\n");
		return -1;
	}

	switch (choice) {
	case 1:
	{
		Ñoordinates_of_point p1, p2, p3, p4;
		/* p1.x = 1.0; p1.y = 1.0;
		p2.x = 3.0; p2.y = 1.0;
		p3.x = 4.0; p3.y = 2.0;
		p4.x = 3.0; p4.y = 1.5; */

		p1.x = 2.0; p1.y = 7.0;
		p2.x = 5.0; p2.y = 4.0;
		p3.x = 9.0; p3.y = 7.0;
		p4.x = 5.0; p4.y = 6.0;

		int check = is_convex(4, p1, p2, p3, p4);

		if (check == 0) {
			printf("The polygon is non-convex");
		}
		else {
			printf("The polygon is convex");
		}
		break;
	}

	case 2:
	{
		double x = 2.0, n = 3.0;
		double result = polynomial(x, n, -1.0, 2.5, 0.0, 3.9);
		printf("The value of your polynomial: %.3lf\n", result);
	}
	}

	return 0;
}