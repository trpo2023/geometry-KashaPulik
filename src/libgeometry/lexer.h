#pragma once
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED_COLOR "\x1b[31m"
#define DEFOLT_COLOR "\x1b[0m"

_Bool input_error(int argc);
_Bool read_error(char* argv[]);
char* copy_letter_sequence(char* str, unsigned int* index);
void tolower_string(char* str, unsigned int index);
_Bool there_is_symbol(char* str, unsigned int index, char symbol);
_Bool is_circle(char* str);
char* copy_part_of_string(char* str, int start, int end);
unsigned int skip_digits(char* str, unsigned int index);
_Bool is_double(char* str, int start, int end);
_Bool this_is_the_end(char* str);
void print_arrow(int column);
void circle_error(char* str, int line, int column);
void line_error(int line);
void bracket_error(char* str, int line, int column, int key);
void comma_error(char* str, int line, int column);
void double_error(char* str, int line, int column);
void unexpected_token_error(char* str, int line, int column);
_Bool empty_string(char* str);
