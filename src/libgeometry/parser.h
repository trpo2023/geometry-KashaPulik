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

listnode* count_instersects(
        listnode* intersects,
        circle* circles,
        unsigned int number,
        unsigned int count);
void read_line(
        char* str,
        unsigned int* line,
        unsigned int* count,
        _Bool key,
        circle** circles,
        unsigned int* buffer_size);
void stdin_read();
void file_read(char* file_name);