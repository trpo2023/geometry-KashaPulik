#include <libgeometry/lexer.h>

_Bool input_error(int argc)
{
    if (argc < 2) {
        printf(RED_COLOR "Error: " DEFOLT_COLOR "no files to read\n");
        return 1;
    }

    if (argc > 2) {
        printf(RED_COLOR "Error: " DEFOLT_COLOR "too many arguments\n");
        return 1;
    }

    return 0;
}

_Bool read_error(char* argv[])
{
    if (fopen(argv[1], "r") == NULL) {
        printf(RED_COLOR "Error: " DEFOLT_COLOR "can't read the file\n");
        return 1;
    }

    return 0;
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

    if (!there_is_symbol(str, index, ')')) {
        free(test_string);
        return 1;
    }

    if (!(there_is_symbol(str, index, ' ')
          && there_is_symbol(str, index, '('))) {
        free(test_string);
        return 0;
    }
    free(test_string);
    return 1;
}

char* copy_part_of_string(char* str, int start, int end)
{
    if (start == end)
        return NULL;
    char* copy = (char*)malloc(256);
    if (copy == NULL)
        return NULL;
    for (int i = start; i < end; i++) {
        copy[i - start] = str[i];
    }
    copy[end] = '\0';
    return copy;
}

unsigned int skip_digits(char* str, unsigned int index)
{
    while (1) {
        if (!isdigit(str[index]))
            return index;
        index++;
    }
}

_Bool is_double(char* str, int start, int end)
{
    char* test_string;
    unsigned int index = 0;

    test_string = copy_part_of_string(str, start, end);
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

void print_arrow(int column)
{
    while (column > 1) {
        printf(" ");
        column--;
    }
    printf("^\n");
}

void circle_error(char* str, int line, int column)
{
    printf("%s", str);

    if (this_is_the_end(str))
        printf("\n");

    print_arrow(column);

    printf(RED_COLOR "Error" DEFOLT_COLOR
                     " at line %d, column %d: expected 'circle'\n",
           line,
           column);
    exit(1);
}

void line_error(int line)
{
    printf(RED_COLOR "Error" DEFOLT_COLOR " at line %d: cannot read the line\n",
           line);
    exit(1);
}

void bracket_error(char* str, int line, int column, int key)
{
    char brackets[3] = "()";
    column++;

    printf("%s", str);

    if (this_is_the_end(str))
        printf("\n");

    print_arrow(column);

    printf(RED_COLOR "Error" DEFOLT_COLOR
                     " in line %d, column %d: expected '%c'\n",
           line,
           column,
           brackets[key]);
    exit(1);
}

void comma_error(char* str, int line, int column)
{
    column++;

    printf("%s", str);

    if (this_is_the_end(str))
        printf("\n");

    print_arrow(column);

    printf(RED_COLOR "Error" DEFOLT_COLOR
                     " at line %d, column %d: expected comma\n",
           line,
           column);
    exit(1);
}

void double_error(char* str, int line, int column)
{
    column++;

    printf("%s", str);

    if (this_is_the_end(str))
        printf("\n");

    print_arrow(column);

    printf(RED_COLOR "Error" DEFOLT_COLOR
                     " in line %d, column %d: expected '<double>'\n",
           line,
           column + 1);
    exit(1);
}

void unexpected_token_error(char* str, int line, int column)
{
    printf("%s", str);

    if (this_is_the_end(str))
        printf("\n");

    print_arrow(column);

    printf(RED_COLOR "Error" DEFOLT_COLOR
                     " in line %d, column %d: unexpected token\n",
           line,
           column + 1);
    exit(1);
}

_Bool empty_string(char* str)
{
    if (*str == '\n') {
        return 1;
    } else {
        return 0;
    }
}