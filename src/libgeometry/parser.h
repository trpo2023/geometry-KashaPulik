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

void circle_output(int number, circle current_circle);
void read_line(char* str, unsigned int* line, unsigned int* count, _Bool key);
void stdin_read();
void file_read(char* file_name);