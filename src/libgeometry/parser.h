#pragma once
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct point {
    double x;
    double y;
} point;

typedef struct circle {
    struct point centre;
    double radius;
} circle;

double string_to_double(char* str, int start, int end);
void circle_output(int number, circle current_circle);
int skip_space(char* str, int line, int column);
int skip_double(char* str, int line, int column);
void read_file(FILE* file);