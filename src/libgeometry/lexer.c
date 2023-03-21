#include <libgeometry/lexer.h>

_Bool this_is_the_end(char* str)
{
    while (1) {
        if (*str == '\n')
            return 0;

        if ((*str == EOF) || (*str == '\0')) {
            return 1;
        }
        str++;
    }
}

void print_arrow(unsigned int column)
{
    while (column > 1) {
        printf(" ");
        column--;
    }
    printf("^\n");
}

void defolt_error_output(
        char* str, unsigned int line, unsigned int column, _Bool key)
{
    column++;
    if (key) {
        printf("%s", str);
        if (this_is_the_end(str))
            printf("\n");
    }

    print_arrow(column);

    printf(RED_COLOR "Error" DEFOLT_COLOR " at line %d, column %d: ",
           line,
           column);
}

void input_error()
{
    printf(RED_COLOR "Error: " DEFOLT_COLOR "too many arguments\n");
}

void read_error()
{
    printf(RED_COLOR "Error: " DEFOLT_COLOR "can't read the file\n");
}

void circle_error(char* str, unsigned int line, unsigned int column, _Bool key)
{
    defolt_error_output(str, line, column, key);
    printf("expected 'circle'\n\n");
}

void bracket_error(
        char* str,
        unsigned int line,
        unsigned int column,
        unsigned int number,
        _Bool key)
{
    number--;
    char brackets[3] = "()";
    defolt_error_output(str, line, column, key);
    printf("expected '%c'\n\n", brackets[number]);
}

void comma_error(char* str, unsigned int line, unsigned int column, _Bool key)
{
    defolt_error_output(str, line, column, key);
    printf("expected comma\n\n");
}

void double_error(char* str, unsigned int line, unsigned int column, _Bool key)
{
    defolt_error_output(str, line, column, key);
    printf("expected '<double>'\n\n");
}

void unexpected_token_error(
        char* str, unsigned int line, unsigned int column, _Bool key)
{
    defolt_error_output(str, line, column, key);
    printf("unexpected token\n\n");
}

double
string_to_double(char* str, unsigned int start_index, unsigned int end_index)
{
    char doublestr[16];
    unsigned int i, j = 0;
    for (i = start_index; i <= end_index; i++) {
        doublestr[j] = str[i];
        j++;
    }
    return atof(doublestr);
}

char* copy_letter_sequence(char* str, unsigned int* index)
{
    char* copy = (char*)malloc(256);
    unsigned int copy_index = 0;
    if (copy == NULL)
        return NULL;
    while (1) {
        if (!isalpha(str[copy_index])) {
            if (copy_index == 0) {
                free(copy);
                return NULL;
            }
            copy[copy_index] = '\0';
            *index = copy_index;
            return copy;
        }
        copy[copy_index] = str[copy_index];
        copy_index++;
    }
}

void tolower_string(char* str, unsigned int index)
{
    unsigned short i;
    for (i = 0; i < index; i++) {
        str[i] = tolower(str[i]);
    }
}

_Bool there_is_symbol(char* str, unsigned int index, char symbol)
{
    if (str[index] == symbol)
        return 1;
    return 0;
}

_Bool is_circle(char* str)
{
    char circle_string[7] = "circle";
    char* test_string;
    unsigned int index = 0;

    test_string = copy_letter_sequence(str, &index);
    if (test_string == NULL)
        return 0;
    tolower_string(test_string, index);

    if (strcmp(test_string, circle_string) != 0) {
        free(test_string);
        return 0;
    }

    free(test_string);
    return 1;
}

char* copy_part_of_string(
        char* str, unsigned int start_index, unsigned int end_index)
{
    if (start_index == end_index)
        return NULL;
    char* copy = (char*)malloc(256);
    if (copy == NULL)
        return NULL;
    for (unsigned int i = start_index; i < end_index; i++) {
        copy[i - start_index] = str[i];
    }
    copy[end_index] = '\0';
    return copy;
}

int skip_space(char* str, unsigned int index)
{
    while (str[index] == ' ')
        index++;

    return index;
}

int skip_double(char* str, unsigned int index)
{
    _Bool check = 1;
    while ((there_is_symbol(str, index, '.')) || (isdigit(str[index]))) {
        check = 0;
        index++;
    }
    if (check)
        return 0;
    return index;
}

unsigned int skip_digits(char* str, unsigned int index)
{
    while (1) {
        if (!isdigit(str[index]))
            return index;
        index++;
    }
}

_Bool is_double(char* str, unsigned int start_index, unsigned int end_index)
{
    char* test_string;
    unsigned int index = 0;

    test_string = copy_part_of_string(str, start_index, end_index);
    if (test_string == NULL)
        return 0;

    if (index == skip_digits(test_string, index)) {
        free(test_string);
        return 0;
    }
    index = skip_digits(test_string, index);

    if (there_is_symbol(test_string, index, '\0')) {
        free(test_string);
        return 1;
    }

    if (!there_is_symbol(test_string, index, '.')) {
        free(test_string);
        return 0;
    }
    index++;

    if (there_is_symbol(test_string, index, '\0')) {
        free(test_string);
        return 0;
    }

    if (index == skip_digits(test_string, index)) {
        free(test_string);
        return 0;
    }

    index = skip_digits(test_string, index);

    if (there_is_symbol(test_string, index, '\0')) {
        free(test_string);
        return 1;
    }

    free(test_string);
    return 0;
}

_Bool empty_string(char* str, unsigned int column)
{
    column = skip_space(str, column);
    if (there_is_symbol(str, column, '\n')) {
        return 1;
    } else if (there_is_symbol(str, column, '\0')) {
        return 1;
    } else {
        return 0;
    }
}

_Bool circle_handling(char* str, unsigned int* index)
{
    if (is_circle(str)) {
        *index = 6;
    } else {
        return 0;
    }
    if (there_is_symbol(str, *index, ' '))
        *index = skip_space(str, *index);
    return 1;
}

_Bool bracket_handling(char* str, unsigned int* index, unsigned short number)
{
    unsigned int buffer_index = *index;
    number--;
    if (number > 1)
        return 0;
    char brackets[3] = "()";
    if (there_is_symbol(str, buffer_index, brackets[number])) {
        buffer_index++;
        *index = skip_space(str, buffer_index);
        return 1;
    } else {
        return 0;
    }
}

_Bool double_handling(char* str, unsigned int* start_index, double* parametr)
{
    unsigned int end_index = skip_double(str, *start_index);
    if (!end_index)
        return 0;
    if (is_double(str, *start_index, end_index)) {
        *parametr = string_to_double(str, *start_index, end_index);
        *start_index = skip_space(str, end_index);
        return 1;
    }
    return 0;
}

_Bool comma_handling(char* str, unsigned int* index)
{
    if (!there_is_symbol(str, *index, ','))
        return 0;
    *index = skip_space(str, *index + 1);
    return 1;
}

_Bool end_handling(char* str, unsigned int index)
{
    if (there_is_symbol(str, index, '\n'))
        return 1;
    if (there_is_symbol(str, index, '\0'))
        return 1;
    return 0;
}