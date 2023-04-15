#pragma once
#include <libgeometry/listnode.h>
#include <libgeometry/parser.h>
#include <stdio.h>

#define RED_COLOR "\x1b[31m"
#define DEFOLT_COLOR "\x1b[0m"

void print_arrow(unsigned int column);
void default_error_output(
        char* str, unsigned int line, unsigned int column, _Bool key);
void input_error();
void read_error();
void circle_error(char* str, unsigned int line, unsigned int column, _Bool key);
void bracket_error(
        char* str,
        unsigned int line,
        unsigned int column,
        unsigned int number,
        _Bool key);
void comma_error(char* str, unsigned int line, unsigned int column, _Bool key);
void double_error(char* str, unsigned int line, unsigned int column, _Bool key);
void unexpected_token_error(
        char* str, unsigned int line, unsigned int column, _Bool key);
void circle_output(int number, circle current_circle, listnode** intersects);
void circles_output(unsigned int count, circle* circles);