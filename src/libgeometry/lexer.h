#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define RED_COLOR "\x1b[31m"
#define DEFOLT_COLOR "\x1b[0m"

_Bool input_error(int argc);
_Bool read_error(char* argv[]);
_Bool is_circle(char* str);
char* copy_part_of_string(char* str, int start, int end);
unsigned int skip_digits(char* str, unsigned int index);
_Bool there_is_symbol(char* str, unsigned int index, char symbol);
_Bool is_double(char* str, int start, int end);
void circleError(char* str, int line, int column);
void lineError(int line);
void bracketError(char* str, int line, int column, int key);
void commaError(char* str, int line, int column);
void doubleError(char* str, int line, int column);
void unTokError(char* str, int line, int column);