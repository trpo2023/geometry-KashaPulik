#pragma once
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED_COLOR "\x1b[31m"
#define DEFOLT_COLOR "\x1b[0m"

_Bool this_is_the_end(char* str);
void print_arrow(unsigned int column);
void defolt_error_output(
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
double
string_to_double(char* str, unsigned int start_index, unsigned int end_index);
char* copy_letter_sequence(char* str, unsigned int* index);
void tolower_string(char* str, unsigned int index);
_Bool there_is_symbol(char* str, unsigned int index, char symbol);
_Bool is_circle(char* str);
char* copy_part_of_string(
        char* str, unsigned int start_index, unsigned int end_index);
int skip_space(char* str, unsigned int index);
int skip_double(char* str, unsigned int index);
unsigned int skip_digits(char* str, unsigned int index);
_Bool is_double(char* str, unsigned int start_index, unsigned int end_index);
_Bool empty_string(char* str, unsigned int column);
_Bool circle_handling(char* str, unsigned int* index);
_Bool bracket_handling(char* str, unsigned int* index, unsigned short number);
_Bool double_handling(char* str, unsigned int* start_index, double* parametr);
_Bool comma_handling(char* str, unsigned int* index);
_Bool end_handling(char* str, unsigned int index);